#include "Renderer/OpenGL/Renderer.h"

Renderer::Renderer( Window* window )
{
  this->window = window;
}

void Renderer::render()
{
  ViewportIterator it( &*this->viewport );

  for( Viewport* v = it.begin(); v != nullptr; v = it.next() )
  {
    ViewportCachedData viewport_cached_data = v->getViewportCachedData();
    glEnable( GL_SCISSOR_TEST );
    glScissor( viewport_cached_data.anchor[0], viewport_cached_data.anchor[1],
      viewport_cached_data.dimensions[0], viewport_cached_data.dimensions[1] );
    
    glClearColor( viewport_cached_data.background[0],
      viewport_cached_data.background[1],
      viewport_cached_data.background[2], 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glViewport( viewport_cached_data.anchor[0], viewport_cached_data.anchor[1],
      viewport_cached_data.dimensions[0], viewport_cached_data.dimensions[1] );

    for( auto scene : v->getScenes() )
    {
      this->drawScene( &*scene );
    }
    glDisable( GL_SCISSOR_TEST );
  }

  glfwSwapBuffers( this->window->getWindow() );
  glfwPollEvents( );
}


void Renderer::drawScene( Scene* scene )
{
  scene->update();
  std::shared_ptr<SceneGraph> scene_graph = scene->getSceneGraph();
  RendererHelper::drawSceneGraph( scene_graph );
}

void Renderer::setViewport( std::shared_ptr<Viewport> viewport )
{
  this->viewport = viewport;
}