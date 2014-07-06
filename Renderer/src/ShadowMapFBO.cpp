#include <stdio.h>
#include "Renderer/ShadowMapFBO.h"


ShadowMapFBO::~ShadowMapFBO()
{
    if (m_fbo != 0) {
        glDeleteFramebuffers(1, &m_fbo);
    }

    if (m_shadowMap != 0) {
        glDeleteTextures(1, &m_shadowMap);
    }
}

ShadowMapFBO::ShadowMapFBO()
{
	int width = 800;
	int height = 600;

	this->shader.reset(new Shader("shadow_map"));

	this->shader->use();
    // Create the FBO
	this->m_fbo = 0;
	glGenFramebuffers(1, &this->m_fbo);

    // Create the depth buffer
	this->m_shadowMap = 0;
	glGenTextures(1, &this->m_shadowMap);
	glBindTexture(GL_TEXTURE_2D, this->m_shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height,
				 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, this->m_fbo);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->m_shadowMap, 0);

    // Disable writes to the color buffer
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

	this->shader->unuse();
}


void ShadowMapFBO::BindForWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->m_fbo);
}


void ShadowMapFBO::BindForReading(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(GL_TEXTURE_2D, this->m_shadowMap);
}
void ShadowMapFBO::ShadowMapPass()
{
	
	this->BindForWriting();

	glClear(GL_DEPTH_BUFFER_BIT);

	for (std::shared_ptr<Model> model_instance: *scene->getModels())
	{
		model_instance->getMesh()->configureShader(this->shader);
		glUniform1i(glGetUniformLocation(shader->shader, "gShadowMap"), 1);
		model_instance->update();
		//models->getMesh()->before_draw();
		//std::vector< std::shared_ptr<Shader> > shaders{ this->shader };
		//this->shader->setUniform("Model", models->getTransformM(), GL_TRUE);
		(*scene->getCamera()).setView((*scene->getLights())[0]->getPosition(), *scene->getCamera()->getTarget());
		ShaderHelper::setCamera(&*this->shader, &*scene->getCamera());
		//models->getMesh()->drawWithShaders(&shaders);
		//models->getMesh()->after_draw();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	this->BindForReading(1);
}
void ShadowMapFBO::setScene(std::shared_ptr<Scene> scene)
{
	this->scene = scene;
}