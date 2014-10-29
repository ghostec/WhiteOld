#ifndef __WHITE_CONTAINABLE__
#define __WHITE_CONTAINABLE__

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <string>
#include "Renderer/Scene.h"
#include "Renderer/Helpers/CameraHelper.h"
#include "WMath/WMath.h"

typedef enum _ContainableSide
{
  CONTAINABLE_SIDE_TOP, CONTAINABLE_SIDE_BOTTOM,
  CONTAINABLE_SIDE_LEFT, CONTAINABLE_SIDE_RIGHT
} ContainableSide;

typedef enum _ContainableAnchorMode
{
  CONTAINABLE_ANCHOR_MODE_RELATIVE,
  CONTAINABLE_ANCHOR_MODE_ABSOLUTE
} ContainableAnchorMode;

typedef enum _ContainableAnchorPosition
{
  CONTAINABLE_ANCHOR_TOP_LEFT,
  CONTAINABLE_ANCHOR_TOP_RIGHT,
  CONTAINABLE_ANCHOR_BOTTOM_LEFT,
  CONTAINABLE_ANCHOR_BOTTOM_RIGHT,
  CONTAINABLE_ANCHOR_CENTER
} ContainableAnchorPosition;

typedef enum _ContainableDimensionsMode
{
  CONTAINABLE_DIMENSIONS_MODE_RELATIVE,
  CONTAINABLE_DIMENSIONS_MODE_ABSOLUTE
} ContainableDimensionsMode;

typedef enum _ContainableMode
{
  CONTAINABLE_MODE_FULL, CONTAINABLE_MODE_BOX,
  CONTAINABLE_MODE_VSPLIT, CONTAINABLE_MODE_HSPLIT
} ContainableMode;

typedef struct _ContainableData
{
  typedef union _ContainableModeData
  {
    typedef struct _ContainableBox
    {
      ContainableAnchorPosition anchor_position;
      ContainableAnchorMode anchor_mode;
      float anchor_x, anchor_y;
      ContainableDimensionsMode dimensions_mode;
      float higher_dimension, aspect_ratio;
    } ContainableBox;

    typedef struct _ContainableSplit
    {
      ContainableSide side;
      ContainableDimensionsMode dimension_mode;
      float size;
    } ContainableSplit;

    ContainableSplit vsplit;
    ContainableSplit hsplit;
    ContainableBox box;
  } ContainableModeData;

  ContainableMode mode;
  ContainableModeData mode_data;
  WMath::vec3 background;

} ContainableData;

typedef struct _ContainableCachedData
{
  WMath::vec2 anchor, dimensions;
  WMath::vec3 background;
} ContainableCachedData;

template< typename T >
class Containable
{
  private:
    ContainableData data;
    ContainableCachedData cached_data;
    std::shared_ptr<T> left_c, right_c;
    bool dirty;
  public:
    Containable( ContainableData data );
    void setLeftChild( std::shared_ptr<T> v ) { this->left_c = v; }
    void setRightChild( std::shared_ptr<T> v ) { this->right_c = v; }
    void setContainableData( ContainableData d ) { data = d; dirty = true; }
    void setContainableCachedData( ContainableCachedData cached_data );
    void setDirty( bool v );
    ContainableData getContainableData() { return this->data; }
    std::shared_ptr<T> getLeftChild() { return left_c; }
    std::shared_ptr<T> getRightChild() { return right_c; }
    bool getDirty() { return this->dirty; }
    ContainableCachedData getContainableCachedData() { return this->cached_data; }
    WMath::vec2 getDimensions();
};

template< typename T >
Containable<T>::Containable( ContainableData data )
{
  this->data = data;
  this->dirty = true;
  this->left_c = nullptr;
  this->right_c = nullptr;
}

template< typename T >
void Containable<T>::setContainableCachedData( ContainableCachedData cached_data )
{
  this->cached_data = cached_data;
}

template< typename T >
void Containable<T>::setDirty( bool v )
{
  if( !v ) this->dirty = v;
  else
  {
    this->dirty = v;
    if( this->left_c ) this->left_c->setDirty( true );
    if( this->right_c ) this->right_c->setDirty( true );
  }
}

template< typename T >
WMath::vec2 Containable<T>::getDimensions()
{
  return this->cached_data.dimensions;
}

template< typename T >
struct PropagatedContainable
{
  WMath::vec2 p_anchor, p_dimensions;
  T* containable;
};

template< typename T, typename P >
class ContainableIterator
{
  private:
    std::queue< PropagatedContainable<T> > bfs_q;
    T* root;
    P* parent;
  public:
    ContainableIterator( T* root, P* parent );
    T* begin();
    T* next();
};

template< typename T, typename P >
ContainableIterator< T, P >::ContainableIterator( T* root, P* parent )
{
  this->root = root;
  this->parent = parent;
}

template< typename T, typename P >
T* ContainableIterator< T, P >::begin()
{
  PropagatedContainable<T> p_root;
  if( parent->getDirty() )
  {
    WMath::vec2 parent_dimensions = parent->getDimensions();
    p_root = { WMath::vec2(0), parent_dimensions, this->root };
    parent->setDirty( false );
    this->root->setDirty( true );
  }
  else
  {
    p_root = { WMath::vec2(0), parent->getDimensions(), this->root };
  }

  bfs_q.push( p_root );
  return this->next();
}

template< typename T, typename P >
T* ContainableIterator< T, P >::next()
{
  if( this->bfs_q.empty() ) return nullptr;

  PropagatedContainable<T> p_c = bfs_q.front(); bfs_q.pop();
  ContainableCachedData containable_cached_data =
    p_c.containable->getContainableCachedData();

  if( p_c.containable->getDirty() )
  {
    ContainableData data = p_c.containable->getContainableData();
    PropagatedContainable<T> p_c_left, p_c_right;
    p_c_left = p_c_right = p_c;
    T* return_el = nullptr;

    if( data.mode == CONTAINABLE_MODE_VSPLIT )
    {
      if( data.mode_data.vsplit.side == CONTAINABLE_SIDE_LEFT )
      {
        if( data.mode_data.vsplit.dimension_mode ==
            CONTAINABLE_DIMENSIONS_MODE_ABSOLUTE )
        {
          p_c_left.p_dimensions[0] = data.mode_data.vsplit.size;
          p_c_right.p_anchor[0] += data.mode_data.vsplit.size;
          p_c_right.p_dimensions[0] -= data.mode_data.vsplit.size;
        }
        else
        {
          p_c_left.p_dimensions[0] =
            data.mode_data.vsplit.size * p_c_left.p_dimensions[0];
          p_c_right.p_anchor[0] += p_c_left.p_dimensions[0];
          p_c_right.p_dimensions[0] -= p_c_left.p_dimensions[0];
        }
      }
      else
      {
        if( data.mode_data.vsplit.dimension_mode ==
            CONTAINABLE_DIMENSIONS_MODE_ABSOLUTE )
        {
          p_c_right.p_dimensions[0] = data.mode_data.vsplit.size;
          p_c_right.p_anchor[0] += p_c.p_dimensions[0] - data.mode_data.vsplit.size;
          p_c_left.p_dimensions[0] -= data.mode_data.vsplit.size;
        }
        else
        {
          p_c_right.p_dimensions[0] =
            data.mode_data.vsplit.size * p_c_right.p_dimensions[0];
          p_c_right.p_anchor[0] += p_c.p_dimensions[0] - p_c_right.p_dimensions[0];
          p_c_left.p_dimensions[0] -= p_c_right.p_dimensions[0];
        }
      }
    }
    else if( data.mode == CONTAINABLE_MODE_BOX )
    {
      WMath::vec2 box_dimensions;

      if( data.mode_data.box.dimensions_mode
          == CONTAINABLE_DIMENSIONS_MODE_ABSOLUTE )
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
      if( data.mode_data.box.anchor_position == CONTAINABLE_ANCHOR_TOP_LEFT )
      {
        if( data.mode_data.box.anchor_mode == CONTAINABLE_ANCHOR_MODE_ABSOLUTE )
        {
          p_c.p_anchor[0] += data.mode_data.box.anchor_x;
          p_c.p_anchor[1] += p_c.p_dimensions[1] -
            data.mode_data.box.anchor_y - box_dimensions[1];
        }
      }

      p_c.p_dimensions = box_dimensions;

      std::cout << p_c.p_dimensions[0] << std::endl;

      p_c_left = p_c_right = p_c;

      return_el = p_c.containable;
    }
    else if( data.mode == CONTAINABLE_MODE_FULL )
    {
      return_el = p_c.containable;
    }

    containable_cached_data.anchor = p_c.p_anchor;
    containable_cached_data.dimensions = p_c.p_dimensions;
    containable_cached_data.background = data.background;
    p_c.containable->setContainableCachedData( containable_cached_data );

    p_c.containable->setDirty( false );

    T* left_c = &*p_c.containable->getLeftChild( );
    if( left_c )
    {
      p_c_left.containable = left_c;
      bfs_q.push( p_c_left );
    }

    T* right_c = &*p_c.containable->getRightChild( );
    if( right_c )
    {
      p_c_right.containable = right_c;
      bfs_q.push( p_c_right );
    }

    if( return_el == nullptr ) return_el = this->next();

    return return_el;
  }
  else
  {
    T* left_c = &*p_c.containable->getLeftChild( );
    if( left_c )
    {
      PropagatedContainable<T> p_c_left;
      p_c_left.p_dimensions = containable_cached_data.dimensions;
      p_c_left.p_anchor = containable_cached_data.anchor;
      p_c_left.containable = left_c;
      bfs_q.push( p_c_left );
    }

    T* right_c = &*p_c.containable->getRightChild( );
    if( right_c )
    {
      PropagatedContainable<T> p_c_right;
      p_c_right.p_dimensions = containable_cached_data.dimensions;
      p_c_right.p_anchor = containable_cached_data.anchor;
      p_c_right.containable = right_c;
      bfs_q.push( p_c_right );
    }

    return p_c.containable;
  }
}

#endif
