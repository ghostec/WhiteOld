#include <iostream>
#include "Renderer/Camera.h"

Camera::Camera( WMath::vec3 position, WMath::vec3 target )
{
  this->position = position;
  this->target = target;
  this->up = WMath::vec3( 0.0f, 1.0f, 0.0f );
  this->view = WMath::lookAtRH( position, target, up );
  this->proj = WMath::OpenGlPerspective( 45.0f, 800.0f / 600.0f, 0.1f, 100.0f );
  this->dirty = true;
}

void Camera::setPosition( WMath::vec3 position )
{
  this->dirty = true;
}

void Camera::setTarget( WMath::vec3 target )
{
  this->dirty = true;
}
