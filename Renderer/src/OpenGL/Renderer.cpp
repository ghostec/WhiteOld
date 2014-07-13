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

    WMath::vec2 d = active_window->getDimensions();

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
  for( std::shared_ptr<Model> model : *model_instances )
  {
    RendererHelper::drawModel( model );
  }
}

void Renderer::addScene( Scene* scene )
{
  this->scenes.push_back( scene );
}

void Renderer::setScenes( std::vector<Scene*> scenes )
{
  this->scenes = scenes;
}