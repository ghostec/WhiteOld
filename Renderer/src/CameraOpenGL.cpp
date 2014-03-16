#include <iostream>
#include "Renderer/CameraOpenGL.h"

CameraOpenGL::CameraOpenGL( WMath::vec3 position, WMath::vec3 target )
{
  this->position = position;
  this->target = target;
  this->up = WMath::vec3( 0.0f, 1.0f, 0.0f );
  this->view = WMath::lookAtRH( position, target, up );
}

void CameraOpenGL::setPosition( WMath::vec3 position )
{
  std::cout << "Placeholder CameraOpenGL::setPosition" << std::endl;
}

void CameraOpenGL::setTarget( WMath::vec3 target )
{
  std::cout << "Placeholder CameraOpenGL::setTarget" << std::endl;
}

void CameraOpenGL::translate( WMath::vec3 vector )
{
  vector = WMath::vec3(0.0f) - vector;
  this->view = this->view * WMath::translate( vector );
}

void CameraOpenGL::rotate( float degree )
{
  degree = -degree;
  this->view = this->view * WMath::rotate_y( degree );
}
