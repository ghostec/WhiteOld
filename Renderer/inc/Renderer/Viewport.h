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

typedef enum _ViewportMode
{
  VIEWPORT_MODE_FULL, VIEWPORT_MODE_COLUMN, VIEWPORT_MODE_ROW, VIEWPORT_MODE_BOX
} ViewportMode;

typedef union _ViewportData
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

} ViewportData;

typedef struct _ViewportCachedData
{
  float x, y, width, height;
} ViewportCachedData;

class Viewport
{
  private:
    WMath::vec2 anchor;
    ViewportMode mode;
    ViewportData data;
    ViewportCachedData cached_data;
    std::vector< std::shared_ptr<Viewport> > children;
    std::vector< std::shared_ptr<Scene> > scenes;
    bool dirty;
  public:
    Viewport();
    Viewport( WMath::vec2 anchor, ViewportData data, ViewportMode mode );
    void addChild( std::shared_ptr<Viewport> v );
    void addScene( std::shared_ptr<Scene> scene );
    void setAnchor( WMath::vec2 a ) { anchor = a; }
    void setViewportData( ViewportData d ) { data = d; dirty = true; }
    void setViewportCachedData( ViewportCachedData cached_data );
    void setDirty( bool dirty ) { this->dirty = dirty; }
    WMath::vec2 getAnchor() { return this->anchor; }
    ViewportData getViewportData() { return this->data; }
    std::vector< std::shared_ptr<Viewport> > getChildren() { return children; }
    std::vector< std::shared_ptr<Scene> > getScenes() { return scenes; }
    bool getDirty() { return this->dirty; }
    ViewportMode getViewportMode() { return this->mode; }
    ViewportCachedData getViewportCachedData() { return this->cached_data; }
};

#endif
