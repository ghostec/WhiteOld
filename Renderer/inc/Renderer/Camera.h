#ifndef __RENDERER_CAMERA_
#define __RENDERER_CAMERA_

#include <string>
#include <memory>
#include "WMath/WMath.h"
#include "WMath/transformations.h"

class Camera
{
  private:
    WMath::vec3 up;
    WMath::vec3 position, target;
    WMath::mat4 view;
    WMath::mat4 proj;
    bool dirty;
  public:
    Camera( WMath::vec3 position, WMath::vec3 target );
    void setPosition( WMath::vec3 position );
    void setTarget( WMath::vec3 target );
    void setDirty( bool value ) { this->dirty = value; };
	void setView(WMath::vec3 position, WMath::vec3 target) { this->view = WMath::lookAtRH(position, target, up); };
    // getters
    WMath::mat4* getView() { return &this->view; };
    WMath::mat4* getProj( ) { return &this->proj; };
	WMath::vec3* getPosition() { return &this->position; };
	WMath::vec3* getTarget() { return &this->target; };
    bool getDirty() { return this->dirty; };
};

#endif
