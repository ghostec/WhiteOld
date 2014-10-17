#include "Renderer/Viewport.h"

Viewport::Viewport( ViewportData data )
{
  this->data = data;
  this->dirty = true;
  this->left_c = nullptr;
  this->right_c = nullptr;
}

void Viewport::setDirty( bool v )
{
  if( !v ) this->dirty = v;
  else
  {
    this->dirty = v;
    if( this->left_c ) this->left_c->setDirty( true );
    if( this->right_c ) this->right_c->setDirty( true );
  }
}

void Viewport::addScene( std::shared_ptr<Scene> scene )
{
  this->scenes.push_back( scene );
}

void Viewport::setViewportCachedData( ViewportCachedData cached_data )
{
  this->cached_data = cached_data;

  for( auto scene : this->scenes )
  {
    CameraHelper::setAspectRatio( &*scene->getCamera(), cached_data.width / cached_data.height );
  }
}

ViewportIterator::ViewportIterator( Viewport* root )
{
  this->root = root;
}

Viewport* ViewportIterator::begin()
{
  PropagatedViewport p_root;
  if( active_window->getDirty() )
  {
    WMath::vec2 window_dimensions = active_window->getDimensions();
    p_root = { WMath::vec2(0), WMath::vec2( window_dimensions ), this->root };
    active_window->setDirty( false );
    this->root->setDirty( true );
  }
  else
  {
    p_root = { WMath::vec2(0), WMath::vec2(0), this->root };
  }

  bfs_q.push( p_root );
    return this->next();
}

Viewport* ViewportIterator::next()
{
  if( this->bfs_q.empty() ) return nullptr;

  PropagatedViewport p_v = bfs_q.front(); bfs_q.pop();
  ViewportCachedData viewport_cached_data =
    p_v.viewport->getViewportCachedData();

  if( p_v.viewport->getDirty() )
  {
    ViewportData data = p_v.viewport->getViewportData();

    if( data.mode == VIEWPORT_MODE_VSPLIT )
    {
      PropagatedViewport p_v_left, p_v_right;
      p_v_left = p_v_right = p_v;

      if( data.mode_data.vsplit.side == VIEWPORT_SIDE_LEFT )
      {
        if( data.mode_data.vsplit.dimension_mode ==
          VIEWPORT_DIMENSIONS_MODE_ABSOLUTE )
        {
          p_v_left.p_dimensions[0] = data.mode_data.vsplit.size;
          p_v_right.p_anchor[0] += data.mode_data.vsplit.size;
          p_v_right.p_dimensions[0] -= data.mode_data.vsplit.size;
        }
        else
        {
          p_v_left.p_dimensions[0] =
            data.mode_data.vsplit.size * p_v_left.p_dimensions[0];
          p_v_right.p_anchor[0] += p_v_left.p_dimensions[0];
          p_v_right.p_dimensions[0] -= p_v_left.p_dimensions[0];
        }
      }
      else
      {
        if( data.mode_data.vsplit.dimension_mode ==
          VIEWPORT_DIMENSIONS_MODE_ABSOLUTE )
        {
          p_v_right.p_dimensions[0] = data.mode_data.vsplit.size;
          p_v_right.p_anchor[0] += p_v.p_dimensions[0] - data.mode_data.vsplit.size;
          p_v_left.p_dimensions[0] -= data.mode_data.vsplit.size;
        }
        else
        {
          p_v_right.p_dimensions[0] =
            data.mode_data.vsplit.size * p_v_right.p_dimensions[0];
          p_v_right.p_anchor[0] += p_v.p_dimensions[0] - p_v_right.p_dimensions[0];
          p_v_left.p_dimensions[0] -= p_v_right.p_dimensions[0];
        }
      }

      viewport_cached_data.x = p_v.p_anchor[0];
      viewport_cached_data.y = p_v.p_anchor[1];
      viewport_cached_data.width = p_v.p_dimensions[0];
      viewport_cached_data.height = p_v.p_dimensions[1];
      viewport_cached_data.background = data.background;
      p_v.viewport->setViewportCachedData( viewport_cached_data );

      Viewport* left_c = &*p_v.viewport->getLeftChild();
      if( left_c )
      {
        p_v_left.viewport = left_c;
        bfs_q.push( p_v_left );
      }

      Viewport* right_c = &*p_v.viewport->getRightChild();
      if( right_c )
      {
        p_v_right.viewport = right_c;
        bfs_q.push( p_v_right );
      }

      p_v.viewport->setDirty( false );

      return this->next();
    }
    else if( data.mode == VIEWPORT_MODE_BOX )
    {
      PropagatedViewport p_v_left, p_v_right;

      WMath::vec2 box_dimensions;

      if( data.mode_data.box.dimensions_mode
        == VIEWPORT_DIMENSIONS_MODE_ABSOLUTE )
      {
        if( data.mode_data.box.aspect_ratio > 1 )
        {
          box_dimensions[0] = data.mode_data.box.higher_dimension;
          box_dimensions[1] = data.mode_data.box.higher_dimension
            / data.mode_data.box.aspect_ratio;
        }
        else
        {
          box_dimensions[1] = data.mode_data.box.higher_dimension;
          box_dimensions[0] = data.mode_data.box.higher_dimension
            * data.mode_data.box.aspect_ratio;
        }
      }
      if( data.mode_data.box.anchor_position == VIEWPORT_ANCHOR_TOP_LEFT )
      {
        
        if( data.mode_data.box.anchor_mode == VIEWPORT_ANCHOR_MODE_ABSOLUTE )
        {
          p_v.p_anchor[0] += data.mode_data.box.anchor_x;
          p_v.p_anchor[1] += p_v.p_dimensions[1] - data.mode_data.box.anchor_y - box_dimensions[1];
        }
        
      }

      p_v.p_dimensions = box_dimensions;

      p_v_left = p_v_right = p_v;

      viewport_cached_data.x = p_v.p_anchor[0];
      viewport_cached_data.y = p_v.p_anchor[1];
      viewport_cached_data.width = p_v.p_dimensions[0];
      viewport_cached_data.height = p_v.p_dimensions[1];
      viewport_cached_data.background = data.background;
      p_v.viewport->setViewportCachedData( viewport_cached_data );

      p_v.viewport->setDirty( false );

      Viewport* left_c = &*p_v.viewport->getLeftChild();
      if( left_c )
      {
        p_v_left.viewport = left_c;
        bfs_q.push( p_v_left );
      }

      std::shared_ptr<Viewport> right_c = p_v.viewport->getRightChild();
      if( right_c )
      {
        p_v_right.viewport = &*right_c;
        bfs_q.push( p_v_right );
      }

      return p_v.viewport;
    }
    else if( data.mode == VIEWPORT_MODE_FULL )
    {
      PropagatedViewport p_v_left, p_v_right;
      p_v_left = p_v_right = p_v;

      viewport_cached_data.x = p_v.p_anchor[0];
      viewport_cached_data.y = p_v.p_anchor[1];
      viewport_cached_data.width = p_v.p_dimensions[0];
      viewport_cached_data.height = p_v.p_dimensions[1];
      viewport_cached_data.background = data.background;
      p_v.viewport->setViewportCachedData( viewport_cached_data );

      p_v.viewport->setDirty( false );

      Viewport* left_c = &*p_v.viewport->getLeftChild( );
      if( left_c )
      {
        p_v_left.viewport = left_c;
        bfs_q.push( p_v_left );
      }

      Viewport* right_c = &*p_v.viewport->getRightChild( );
      if( right_c )
      {
        p_v_right.viewport = right_c;
        bfs_q.push( p_v_right );
      }

      return p_v.viewport;
    }
  }
  else
  {
    Viewport* left_c = &*p_v.viewport->getLeftChild( );
    if( left_c )
    {
      PropagatedViewport p_v_left;
      p_v_left.p_dimensions =
        WMath::vec2( viewport_cached_data.width, viewport_cached_data.height );
      p_v_left.p_anchor =
        WMath::vec2( viewport_cached_data.x, viewport_cached_data.y );
      p_v_left.viewport = left_c;
      bfs_q.push( p_v_left );
    }

    Viewport* right_c = &*p_v.viewport->getRightChild( );
    if( right_c )
    {
      PropagatedViewport p_v_right;
      p_v_right.p_dimensions =
        WMath::vec2( viewport_cached_data.width, viewport_cached_data.height );
      p_v_right.p_anchor =
        WMath::vec2( viewport_cached_data.x, viewport_cached_data.y );
      p_v_right.viewport = right_c;
      bfs_q.push( p_v_right );
    }

    return p_v.viewport;
  }
}