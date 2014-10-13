#include "Renderer/Viewport.h"

Viewport::Viewport( ViewportData data )
{
  this->data = data;
  this->dirty = true;
}

void Viewport::addChild( std::shared_ptr<Viewport> v )
{
  this->children.push_back( v );
}

void Viewport::addScene( std::shared_ptr<Scene> scene )
{
  this->scenes.push_back( scene );
}

void Viewport::setViewportCachedData( ViewportCachedData cached_data )
{
  this->cached_data = cached_data;

  for( auto c : this->children ) c->setDirty( true );

  for( auto scene : this->scenes )
  {
    CameraHelper::setAspectRatio( &*scene->getCamera(), cached_data.width / cached_data.height );
  }

  this->dirty = false;
}

ViewportIterator::ViewportIterator( Viewport* begin )
{
  this->begin = begin;

  this->begin->setDirty( true );

  PropagatedViewport root =
    { WMath::vec2( 0 ), WMath::vec2( 800, 600 ), this->begin };

  bfs_q.push( root ); bfs_v.push_back( this->begin );
}

bool ViewportIterator::hasNext()
{
  if( !this->bfs_q.empty() )  return true;
  else                        return false;
}

Viewport* ViewportIterator::next()
{
  PropagatedViewport p_v = bfs_q.front(); bfs_q.pop();
  ViewportCachedData viewport_cached_data = p_v.viewport->getViewportCachedData( );

  if( p_v.viewport->getDirty() )
  {
    ViewportData viewport_data = p_v.viewport->getViewportData( );

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

    for( auto c : p_v.viewport->getChildren() )
    {
      if( std::find( bfs_v.begin(), bfs_v.end(), &*c ) == bfs_v.end( ) )
      {
        p_v.viewport = &*c;
        bfs_q.push( p_v ); bfs_v.push_back( &*c );
      }
    }

  }

  return p_v.viewport;
}