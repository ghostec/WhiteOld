#ifndef __WHITE_CAMERA_
#define __WHITE_CAMERA_

#include "WMath/WMath.h"
#include "WMath/transformations.h"

class Camera
{
  private:
    WMath::vec3 up;
    WMath::vec3 position, target;
    WMath::mat4 view;
  public:
    Camera( WMath::vec3 position, WMath::vec3 target );
    void setPosition( WMath::vec3 position );
    void setTarget( WMath::vec3 target );
    WMath::mat4* getView() { return &this->view; };
    void translate( WMath::vec3 vector );
    void rotate( float degree );
};

#endif
