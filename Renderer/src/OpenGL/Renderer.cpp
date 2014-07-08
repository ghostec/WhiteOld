#include "Renderer/OpenGL/Renderer.h"

Renderer::Renderer( Window* window )
{
  this->window = window;
}

void Renderer::render()
{
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for( Scene* scene : this->scenes )
    {
      this->drawScene( scene );
    }

    glfwSwapBuffers( this->window->getWindow() );
    glfwPollEvents();
}


void Renderer::drawScene( Scene* scene )
{
  scene->update();
  std::vector< std::shared_ptr<Model> >*
    model_instances = scene->getModels();
  for( std::shared_ptr<Model> model_instance : *model_instances )
  {
    this->drawModel( model_instance );
  }
}

void Renderer::drawModel( std::shared_ptr<Model> model )
{
  model->update();
  std::shared_ptr<Mesh> mesh = model->getMesh();
  std::shared_ptr<Shader> shader = model->getShader();

  glBindVertexArray( mesh->getVAO() );
  shader->use();

  if( model->getModelType() == MODEL_2D )
    { glDisable( GL_DEPTH_TEST ); }
  else
    { glEnable( GL_DEPTH_TEST ); }

  glDrawArrays( GL_TRIANGLES, 0, mesh->getVerticesCount() );

  shader->unuse();
  glBindVertexArray( 0 );
}

void Renderer::addScene( Scene* scene )
{
  this->scenes.push_back( scene );
}
