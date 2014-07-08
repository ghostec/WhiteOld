#include "Renderer/Helpers/CameraHelper.h"

namespace CameraHelper
{
  void TargetCamera
    ( Camera* camera, WMath::vec3 position, WMath::vec3 target )
  {
    WMath::vec3 up = WMath::vec3( 0.0f, 1.0f, 0.0f );
    camera->setView( WMath::lookAtRH( position, target, up ) );
    camera->setProj
      ( WMath::OpenGlPerspective( 45.0f, 800.0f / 600.0f, 0.1f, 100.0f ) );
  }
};