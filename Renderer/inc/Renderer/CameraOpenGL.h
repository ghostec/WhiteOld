#ifndef __WHITE_CAMERAOPENGL__
#define __WHITE_CAMERAOPENGL__

#include "Renderer/Camera.h"

class CameraOpenGL : public Camera
{
  private:
    WMath::vec3 up;
  public:
    CameraOpenGL( WMath::vec3 position, WMath::vec3 target );
    void setPosition( WMath::vec3 position );
    void setTarget( WMath::vec3 target );
    WMath::mat4 getView() { return this->view; };
    void translate( WMath::vec3 vector );
    void rotate( float degree );
};

#endif
