#include "Renderer/Light.h"

Light::Light( WMath::vec3 position, WMath::vec3 color,
              float attenuation, float ambient_coefficient )
{
  this->position = position;
  this->color = color;
  this->attenuation = attenuation;
  this->ambient_coefficient = ambient_coefficient;
}

void Light::setPosition( WMath::vec3 position )
{
  this->position = position;
  this->notify( "DIRTY" );
}