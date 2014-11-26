#include <iostream>
#include "Renderer/Camera.h"

Camera::Camera()
{
  this->proj_type = CAMERA_PROJECTION_PERSPECTIVE;
  this->view = WMath::mat4();
  this->proj = WMath::mat4();
  this->dirty = true;
}

void Camera::setProjectionType( CameraProjectionType t )
{
  this->proj_type = t;
}