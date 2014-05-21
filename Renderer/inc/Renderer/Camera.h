#ifndef __WHITE_CAMERA_
#define __WHITE_CAMERA_

#include <string>
#include "Helpers/Observable.h"
#include "WMath/WMath.h"
#include "WMath/transformations.h"

class Camera : public Observable<std::string>
{
  private:
    WMath::vec3 up;
    WMath::vec3 position, target;
    WMath::mat4 view;
    WMath::mat4 proj;
  public:
    Camera( WMath::vec3 position, WMath::vec3 target );
    void setPosition( WMath::vec3 position );
    void setTarget( WMath::vec3 target );
    // getters
    WMath::mat4* getView() { return &this->view; };
    WMath::mat4* getProj() { return &this->proj; };
};

#endif
