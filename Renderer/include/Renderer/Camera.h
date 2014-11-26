#ifndef __RENDERER_CAMERA_
#define __RENDERER_CAMERA_

#include <string>
#include <memory>
#include "Renderer/Window.h"
#include "Renderer/Helpers/CameraHelper.h"
#include "WMath/WMath.h"
#include "WMath/transformations.h"

enum CameraProjectionType
{
  CAMERA_PROJECTION_PERSPECTIVE, CAMERA_PROJECTION_ORTHOGRAPHIC
};

class Camera
{
  private:
    CameraProjectionType proj_type;
    WMath::mat4 view;
    WMath::mat4 proj;
    bool dirty;
  public:
    Camera();
    // setView
    void setView( WMath::mat4 view ) { this->view = view; }
    void setProj( WMath::mat4 proj ) { this->proj = proj; }
    void setDirty( bool value ) { this->dirty = value; };
    void setProjectionType( CameraProjectionType t );
    // getters
    WMath::mat4* getView() { return &this->view; };
    WMath::mat4* getProj( ) { return &this->proj; };
    bool getDirty() { return this->dirty; };
    CameraProjectionType getProjectionType() { return this->proj_type; }
};

#endif
