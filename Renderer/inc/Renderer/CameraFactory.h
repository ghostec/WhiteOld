#ifndef __WHITE_CAMERAFACTORY__
#define __WHITE_CAMERAFACTORY__

#include "Renderer/Camera.h"
#include "Renderer/CameraOpenGL.h"

class CameraFactory
{
  public:
    virtual Camera* createCamera( WMath::vec3 position, WMath::vec3 target ) = 0;
};

class CameraFactoryOpenGL : public CameraFactory
{
  public:
    Camera* createCamera( WMath::vec3 position, WMath::vec3 target );
};

#endif
