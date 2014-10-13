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

  std::queue< PropagatedViewport > bfs_q;
  std::vector< std::shared_ptr<Viewport> > bfs_v;

  this->viewport->setDirty( true );

  PropagatedViewport root =
    { WMath::vec2(0), WMath::vec2( window_dimensions ), this->viewport };

  bfs_q.push( root ); bfs_v.push_back( this->viewport );

  while( !bfs_q.empty() )
  {
    PropagatedViewport p_v = bfs_q.front(); bfs_q.pop();
    ViewportCachedData viewport_cached_data = p_v.viewport->getViewportCachedData();

    if( p_v.viewport->getDirty() )
    {
      ViewportData viewport_data = p_v.viewport->getViewportData(); 

      if( viewport_data.anchor_mode == VIEWPORT_ANCHOR_MODE_ABSOLUTE )
      {
        if( viewport_data.anchor_corner == VIEWPORT_ANCHOR_CORNER_TOP_LEFT )
        {
          p_v.p_anchor = p_v.p_anchor +
            WMath::vec2( viewport_data.anchor[0], viewport_data.anchor[1] );
        }
        else if( viewport_data.anchor_corner == VIEWPORT_ANCHOR_CORNER_TOP_RIGHT )
        {
          p_v.p_anchor = p_v.p_anchor +
            WMath::vec2( 0, viewport_data.anchor[1] );
        }
      }
      else
      {
        if( viewport_data.anchor_corner == VIEWPORT_ANCHOR_CORNER_TOP_LEFT )
        {
          p_v.p_anchor = p_v.p_anchor +
            WMath::vec2( viewport_data.anchor[0] * p_v.p_dimensions[0],
            viewport_data.anchor[1] * p_v.p_dimensions[1] );
        }
        else if( viewport_data.anchor_corner == VIEWPORT_ANCHOR_CORNER_TOP_RIGHT )
        {
          p_v.p_anchor = p_v.p_anchor +
            WMath::vec2( viewport_data.anchor[0] * p_v.p_dimensions[0],
            viewport_data.anchor[1] * p_v.p_dimensions[1] );
        }
      }

      if( viewport_data.mode == VIEWPORT_MODE_BOX )
      {
        if( viewport_data.mode_data.box.aspect_ratio > 1 )
        {
          p_v.p_dimensions[0] = p_v.p_dimensions[0] * viewport_data.mode_data.box.higher_dimension;
          p_v.p_dimensions[1] = p_v.p_dimensions[0] / viewport_data.mode_data.box.aspect_ratio;
        }
        else
        {
          p_v.p_dimensions[1] = p_v.p_dimensions[1] * viewport_data.mode_data.box.higher_dimension;
          p_v.p_dimensions[0] = p_v.p_dimensions[1] * viewport_data.mode_data.box.aspect_ratio;
        }
      }
      else if( viewport_data.mode == VIEWPORT_MODE_COLUMN )
      {
        p_v.p_dimensions[0] = p_v.p_dimensions[0] * viewport_data.mode_data.column.size;
      }
      else if( viewport_data.mode == VIEWPORT_MODE_ROW )
      {
        p_v.p_dimensions[1] = p_v.p_dimensions[1] * viewport_data.mode_data.column.size;
      }

      if( viewport_data.anchor_corner == VIEWPORT_ANCHOR_CORNER_TOP_RIGHT )
      {
        if( viewport_data.anchor_mode == VIEWPORT_ANCHOR_MODE_ABSOLUTE )
        {
          p_v.p_dimensions[0] -= viewport_data.anchor[0];
        }
      }
        
      viewport_cached_data.width = p_v.p_dimensions[0];
      viewport_cached_data.height = p_v.p_dimensions[1];
      viewport_cached_data.x = p_v.p_anchor[0];
      viewport_cached_data.y = p_v.p_anchor[1];
      viewport_cached_data.background = viewport_data.background;
      p_v.viewport->setViewportCachedData( viewport_cached_data );

    }

    glEnable( GL_SCISSOR_TEST );
    glScissor( viewport_cached_data.x, viewport_cached_data.y,
      viewport_cached_data.width, viewport_cached_data.height ); 
    
    glClearColor( viewport_cached_data.background[0],
      viewport_cached_data.background[1],
      viewport_cached_data.background[2], 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glViewport( viewport_cached_data.x, viewport_cached_data.y,
      viewport_cached_data.width, viewport_cached_data.height );

    for( auto scene : p_v.viewport->getScenes() )
    {
      this->drawScene( &*scene );
    }

    for( auto c : p_v.viewport->getChildren() )
    {
      if( std::find( bfs_v.begin(), bfs_v.end(), c ) == bfs_v.end() )
      {
        p_v.viewport = c;
        bfs_q.push( p_v ); bfs_v.push_back( c );
      }
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