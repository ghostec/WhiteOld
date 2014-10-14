#ifndef __WHITE_VIEWPORT__
#define __WHITE_VIEWPORT__

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <string>
#include "Renderer/Scene.h"
#include "Renderer/Helpers/CameraHelper.h"
#include "WMath/WMath.h"

typedef enum _ViewportSide
{
  VIEWPORT_SIDE_TOP, VIEWPORT_SIDE_BOTTOM,
  VIEWPORT_SIDE_LEFT, VIEWPORT_SIDE_RIGHT
} ViewportSide;

typedef enum _ViewportAnchorMode
{
  VIEWPORT_ANCHOR_MODE_RELATIVE,
  VIEWPORT_ANCHOR_MODE_ABSOLUTE
} ViewportAnchorMode;

typedef enum _ViewportAnchorPosition
{
  VIEWPORT_ANCHOR_TOP_LEFT,
  VIEWPORT_ANCHOR_TOP_RIGHT,
  VIEWPORT_ANCHOR_BOTTOM_LEFT,
  VIEWPORT_ANCHOR_BOTTOM_RIGHT,
  VIEWPORT_ANCHOR_CENTER
} ViewportAnchorPosition;

typedef enum _ViewportDimensionsMode
{
  VIEWPORT_DIMENSIONS_MODE_RELATIVE,
  VIEWPORT_DIMENSIONS_MODE_ABSOLUTE
} ViewportDimensionsMode;

typedef enum _ViewportMode
{
  VIEWPORT_MODE_FULL, VIEWPORT_MODE_BOX,
  VIEWPORT_MODE_VSPLIT, VIEWPORT_MODE_HSPLIT
} ViewportMode;

typedef struct _ViewportData
{
  typedef union _ViewportModeData
  {
    typedef struct _ViewportBox
    {
      ViewportAnchorPosition anchor_position;
      ViewportAnchorMode anchor_mode;
      float anchor_x, anchor_y;
      ViewportDimensionsMode dimensions_mode;
      float higher_dimension, aspect_ratio;
    } ViewportBox;

    typedef struct _ViewportSplit
    {
      ViewportSide side;
      ViewportDimensionsMode dimension_mode;
      float size;
    } ViewportSplit;

    ViewportSplit vsplit;
    ViewportSplit hsplit;
    ViewportBox box;
  } ViewportModeData;

  ViewportMode mode;
  ViewportModeData mode_data;
  WMath::vec3 background;

} ViewportData;

typedef struct _ViewportCachedData
{
  float x, y, width, height;
  WMath::vec3 background;
} ViewportCachedData;

class Viewport
{
  private:
    ViewportData data;
    ViewportCachedData cached_data;
    std::shared_ptr<Viewport> left_c, right_c;
    std::vector< std::shared_ptr<Scene> > scenes;
    bool dirty;
  public:
    Viewport( ViewportData data );
    void setLeftChild( std::shared_ptr<Viewport> v ) { this->left_c = v; }
    void setRightChild( std::shared_ptr<Viewport> v ) { this->right_c = v; }
    void addScene( std::shared_ptr<Scene> scene );
    void setViewportData( ViewportData d ) { data = d; dirty = true; }
    void setViewportCachedData( ViewportCachedData cached_data );
    void setDirty( bool dirty );
    ViewportData getViewportData() { return this->data; }
    std::shared_ptr<Viewport> getLeftChild() { return left_c; }
    std::shared_ptr<Viewport> getRightChild() { return right_c; }
    std::vector< std::shared_ptr<Scene> > getScenes() { return scenes; }
    bool getDirty() { return this->dirty; }
    ViewportCachedData getViewportCachedData() { return this->cached_data; }
};

typedef struct _PropagatedViewport
{
  WMath::vec2 p_anchor, p_dimensions;
  Viewport* viewport;
} PropagatedViewport;

class ViewportIterator
{
  private:
    std::queue< PropagatedViewport > bfs_q;
    Viewport* root;
  public:
    ViewportIterator( Viewport* root );
    Viewport* begin();
    Viewport* next();
};

#endif
