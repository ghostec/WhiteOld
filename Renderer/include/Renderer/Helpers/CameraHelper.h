#ifndef __RENDERER_HELPERS_CAMERAHELPER_
#define __RENDERER_HELPERS_CAMERAHELPER_

#include "Renderer/Camera.h"
#include "Renderer/Window.h"
#include "WMath/WMath.h"
#include "WMath/transformations.h"

class Camera;

namespace CameraHelper
{
  void targetCamera
    ( Camera* camera, WMath::vec3 position, WMath::vec3 target );
  void normalCamera( Camera* camera, float viewport_aspect_ratio );
  void setAspectRatio( Camera* camera, float aspect_ratio );
  void updateWindow( Camera* camera );
};

#endif
