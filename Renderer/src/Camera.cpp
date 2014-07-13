#include <iostream>
#include "Renderer/Camera.h"

Camera::Camera()
{
  this->dirty = true;
}

void Camera::update()
{
  if( active_window->getDirty() )
  {
    CameraHelper::updateWindow( this, active_window );
    active_window->setDirty( false );
  } 
}