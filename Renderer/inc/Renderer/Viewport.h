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

typedef enum _ViewportAnchorCorner
{
  VIEWPORT_ANCHOR_CORNER_TOP_LEFT,
  VIEWPORT_ANCHOR_CORNER_TOP_RIGHT,
  VIEWPORT_ANCHOR_CORNER_BOTTOM_LEFT,
  VIEWPORT_ANCHOR_CORNER_BOTTOM_RIGHT
} ViewportAnchorCorner;

typedef enum _ViewportDimensionsMode
{
  VIEWPORT_DIMENSIONS_MODE_RELATIVE,
  VIEWPORT_DIMENSIONS_MODE_ABSOLUTE
} ViewportDimensionsMode;

typedef enum _ViewportAnchorMode
{
  VIEWPORT_ANCHOR_MODE_RELATIVE,
  VIEWPORT_ANCHOR_MODE_ABSOLUTE
} ViewportAnchorMode;

typedef enum _ViewportMode
{
  VIEWPORT_MODE_FULL, VIEWPORT_MODE_COLUMN, VIEWPORT_MODE_ROW, VIEWPORT_MODE_BOX
} ViewportMode;

typedef struct _ViewportData
{
  typedef union _ViewportModeData
  {
    typedef struct _ViewportRow
    {
      float size;
    } ViewportRow;

    typedef struct _ViewportColumn
    {
      float size;
    } ViewportColumn;

    typedef struct _ViewportBox
    {
      float higher_dimension, aspect_ratio;
    } ViewportBox;

    ViewportRow row;
    ViewportColumn column;
    ViewportBox box;
  } ViewportModeData;

  ViewportMode mode;
  ViewportModeData mode_data;
  ViewportDimensionsMode dimensions_mode;
  ViewportAnchorCorner anchor_corner;
  ViewportAnchorMode anchor_mode;
  WMath::vec2 anchor;
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
    std::vector< std::shared_ptr<Viewport> > children;
    std::vector< std::shared_ptr<Scene> > scenes;
    bool dirty;
  public:
    Viewport( ViewportData data );
    void addChild( std::shared_ptr<Viewport> v );
    void addScene( std::shared_ptr<Scene> scene );
    void setViewportData( ViewportData d ) { data = d; dirty = true; }
    void setViewportCachedData( ViewportCachedData cached_data );
    void setDirty( bool dirty ) { this->dirty = dirty; }
    ViewportData getViewportData() { return this->data; }
    std::vector< std::shared_ptr<Viewport> > getChildren() { return children; }
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
    std::vector< Viewport* > bfs_v;
    Viewport* begin;
  public:
    ViewportIterator( Viewport* begin );
    bool hasNext();
    Viewport* next();
};

#endif
