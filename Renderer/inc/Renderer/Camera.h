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
    // getters
    std::shared_ptr<WMath::mat4> getView() { return std::make_shared<WMath::mat4>( this->view ); };
    std::shared_ptr<WMath::mat4> getProj( ) { return std::make_shared<WMath::mat4>( this->proj ); };
    bool getDirty() { return this->dirty; };
};

#endif
