#include "Renderer/Viewport.h"

Viewport::Viewport( ContainableData data ) : Containable<Viewport>( data )
{
}

void Viewport::addScene( std::shared_ptr<Scene> scene )
{
  this->scenes.push_back( scene );
}

void Viewport::setContainableCachedData( ContainableCachedData cached_data )
{
  Containable<Viewport>::setContainableCachedData( cached_data );

  for( auto scene : this->scenes )
  {
    Camera* camera = &*scene->getCamera();
    if( camera->getProjectionType() == CAMERA_PROJECTION_PERSPECTIVE )
    CameraHelper::setAspectRatio( camera,
      cached_data.dimensions[0] / cached_data.dimensions[1] );
  }
}
