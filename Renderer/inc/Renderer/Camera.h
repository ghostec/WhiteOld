#ifndef __RENDERER_CAMERA_
#define __RENDERER_CAMERA_

#include <string>
#include <memory>
#include "WMath/WMath.h"
#include "WMath/transformations.h"

class Camera
{
  private:
    WMath::mat4 view;
    WMath::mat4 proj;
    bool dirty;
  public:
    Camera();
    // setView
    void setView( WMath::mat4 view ) { this->view = view; }
    void setProj( WMath::mat4 proj ) { this->proj = proj; }
    void setDirty( bool value ) { this->dirty = value; };
    // getters
    WMath::mat4* getView() { return &this->view; };
    WMath::mat4* getProj( ) { return &this->proj; };
    bool getDirty() { return this->dirty; };
};

#endif
