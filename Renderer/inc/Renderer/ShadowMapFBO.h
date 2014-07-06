#ifndef SHADOWMAPFBO_H
#define	SHADOWMAPFBO_H

#include <GL/glew.h>
#include "Renderer/Shader.h"
#include "Renderer/Scene.h"

class ShadowMapFBO
{
private:
	GLuint m_fbo;
	GLuint m_shadowMap;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Scene> scene;
public:
    ShadowMapFBO();

    ~ShadowMapFBO();

    bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

    void BindForWriting();

    void BindForReading(GLenum TextureUnit);
	
	void ShadowMapPass();

	void setScene(std::shared_ptr<Scene> scene);
};

#endif	/* SHADOWMAPFBO_H */

