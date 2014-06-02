#ifndef __RENDERER_LIGHT__
#define __RENDERER_LIGHT__

#include <string>
#include "WMath/WMath.h"

class Light
{
  private:
    WMath::vec3 position;
    WMath::vec3 color;
    float attenuation;
    float ambient_coefficient;
    bool dirty;
  public:
    Light(  WMath::vec3 position, WMath::vec3 color, 
            float attenuation, float ambient_coefficient );
    void setPosition( WMath::vec3 position );
    WMath::vec3 getPosition() { return this->position; };
    void setDirty( bool value ) { this->dirty = value; };
    bool getDirty( ) { return this->dirty; };
};

#endif
