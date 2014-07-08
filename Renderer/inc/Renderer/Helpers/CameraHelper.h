#ifndef __RENDERER_HELPERS_CAMERAHELPER_
#define __RENDERER_HELPERS_CAMERAHELPER_

#include "Renderer/Camera.h"
#include "WMath/WMath.h"
#include "WMath/transformations.h"

namespace CameraHelper
{
  void TargetCamera
    ( Camera* camera, WMath::vec3 position, WMath::vec3 target );
};

#endif
