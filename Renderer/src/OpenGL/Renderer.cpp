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

  for( auto node : scene_graph->getNode( "root" )->getChildren() )
  {
    RendererHelper::drawSGNode( node );
  }

  PropagatedSGNodeData propagated_node_data;
  PropagatedSGNode propagated_node =
    { scene_graph->getNodes()[0], propagated_node_data };

  //RendererHelper::drawPropagatedSGNode( propagated_node );
}

void Renderer::addScene( Scene* scene )
{
  this->scenes.push_back( scene );
}

void Renderer::setScenes( std::vector<Scene*> scenes )
{
  this->scenes = scenes;
}