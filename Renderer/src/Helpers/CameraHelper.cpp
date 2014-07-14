#include "Renderer/Helpers/CameraHelper.h"

namespace CameraHelper
{
  void targetCamera
    ( Camera* camera, WMath::vec3 position, WMath::vec3 target )
  {
    WMath::vec3 up = WMath::vec3( 0.0f, 1.0f, 0.0f );
    camera->setView( WMath::lookAtRH( position, target, up ) );
    WMath::vec2 d = active_window->getDimensions();
    camera->setProj
      ( WMath::OpenGlPerspective( 45.0f, d[0] / d[1], 0.1f, 100.0f ) );
  }

  void normalCamera( Camera* camera )
  {
    WMath::mat4 view;
    camera->setView( view );
    WMath::vec2 d = active_window->getDimensions( );
    camera->setProj
      ( WMath::OpenGlPerspective( 45.0f, d[0] / d[1], 0.1f, 100.0f ) );
  }

  void updateWindow( Camera* camera )
  {
    WMath::vec2 d = active_window->getDimensions();
    camera->setProj
      ( WMath::OpenGlPerspective( 45.0f, d[0] / d[1], 0.1f, 100.0f ) );
  }
};