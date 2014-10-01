#include "Renderer/OpenGL/Renderer.h"

Renderer::Renderer( Window* window )
{
  this->window = window;
}

void Renderer::render()
{
    // Clear the screen to black
    glClearColor(0.80f, 0.80f, 0.80f, 1.0f);
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
  std::shared_ptr<SceneGraph> scene_graph = scene->getSceneGraph();

  //std::cout << scene_graph->getNodes().size() << std::endl;

  for( std::shared_ptr<SGNode> sg_node : scene_graph->getNodes() )
  {
    RendererHelper::drawSGNode( sg_node );
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