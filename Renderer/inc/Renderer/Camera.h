#ifndef __WHITE_CAMERA_
#define __WHITE_CAMERA_

#include "WMath/WMath.h"

class Camera
{
  protected:
    WMath::vec3 position, target;
    WMath::mat4 view;
  public:
    virtual void setPosition( WMath::vec3 position ) = 0;
    virtual void setTarget( WMath::vec3 target ) = 0;
    virtual WMath::mat4 getView() = 0;
    virtual void translate( WMath::vec3 vector ) = 0;
    virtual void rotate( float degree ) = 0;
};

#endif
