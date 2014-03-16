#include "Renderer/CameraFactory.h"
#include <iostream>

Camera* CameraFactoryOpenGL::createCamera( WMath::vec3 position,
                                          WMath::vec3 target )
{
  return new CameraOpenGL( position, target );
}
