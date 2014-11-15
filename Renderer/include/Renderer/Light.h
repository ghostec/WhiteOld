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
    // setters
    void setPosition( WMath::vec3 position );
    void setAttenuation( float v ) { this->attenuation = v; }
    void setAmbientCoefficient( float v ) { this->ambient_coefficient= v; }
    // getters
    WMath::vec3 getPosition() { return this->position; };
    WMath::vec3 getColor() { return this->color; };
    float getAttenuation() { return this->attenuation; }
    float getAmbientCoefficient() { return this->ambient_coefficient; }
    void setDirty( bool value ) { this->dirty = value; };
    bool getDirty( ) { return this->dirty; };
};

#endif
