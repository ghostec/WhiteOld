#ifndef __RENDERER_LIGHT__
#define __RENDERER_LIGHT__

#include <string>
#include "WMath/WMath.h"
#include "Helpers/Observable.h"

class Light : public Observable<std::string>
{
  private:
    WMath::vec3 position;
    WMath::vec3 color;
    float attenuation;
    float ambient_coefficient;
  public:
    Light(  WMath::vec3 position, WMath::vec3 color, 
            float attenuation, float ambient_coefficient );
    void setPosition( WMath::vec3 position );
    WMath::vec3 getPosition() { return this->position; };
};

#endif
