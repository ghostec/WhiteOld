#include "Renderer/OpenGL/Renderer.h"

Renderer::Renderer( Window* window )
{
  this->window = window;
  ViewportData data;
  data.mode = VIEWPORT_MODE_FULL;
  data.anchor = WMath::vec2(0);
  data.anchor_mode = VIEWPORT_ANCHOR_MODE_ABSOLUTE;
  data.anchor_corner = VIEWPORT_ANCHOR_CORNER_TOP_LEFT;
  data.dimensions_mode = VIEWPORT_DIMENSIONS_MODE_RELATIVE;
  data.background = WMath::vec3( 1.0 );
  this->viewport.reset( new Viewport(data) );
}

void Renderer::render()
{
  WMath::vec2 window_dimensions = this->window->getDimensions();

  ViewportIterator it( &*this->viewport );

  while( it.hasNext() )
  {
    Viewport* v = it.next();
    ViewportCachedData viewport_cached_data = v->getViewportCachedData();
    glEnable( GL_SCISSOR_TEST );
    glScissor( viewport_cached_data.x, viewport_cached_data.y,
      viewport_cached_data.width, viewport_cached_data.height ); 
    
    glClearColor( viewport_cached_data.background[0],
      viewport_cached_data.background[1],
      viewport_cached_data.background[2], 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glViewport( viewport_cached_data.x, viewport_cached_data.y,
      viewport_cached_data.width, viewport_cached_data.height );

    for( auto scene : v->getScenes() )
    {
      this->drawScene( &*scene );
    }
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

void Renderer::addViewport( std::shared_ptr<Viewport> viewport )
{
  this->viewport->addChild( viewport );
}