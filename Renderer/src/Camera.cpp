#include <iostream>
#include "Renderer/Camera.h"

Camera::Camera( WMath::vec3 position, WMath::vec3 target )
{
  this->position = position;
  this->target = target;
  this->up = WMath::vec3( 0.0f, 1.0f, 0.0f );
  this->view = WMath::lookAtRH( position, target, up );
}

void Camera::setPosition( WMath::vec3 position )
{
  std::cout << "Placeholder Camera::setPosition" << std::endl;
}

void Camera::setTarget( WMath::vec3 target )
{
  std::cout << "Placeholder Camera::setTarget" << std::endl;
}

void Camera::translate( WMath::vec3 vector )
{
  vector = WMath::vec3(0.0f) - vector;
  this->view = this->view * WMath::translate( vector );
}

void Camera::rotate( float degree )
{
  degree = -degree;
  this->view = this->view * WMath::rotate_y( degree );
}
