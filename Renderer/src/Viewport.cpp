#include "Renderer/Viewport.h"

Viewport::Viewport( ViewportData data )
{
  this->data = data;
  this->dirty = true;
}

void Viewport::addChild( std::shared_ptr<Viewport> v )
{
  this->children.push_back( v );
}

void Viewport::addScene( std::shared_ptr<Scene> scene )
{
  this->scenes.push_back( scene );
}

void Viewport::setViewportCachedData( ViewportCachedData cached_data )
{
  this->cached_data = cached_data;

  for( auto c : this->children ) c->setDirty( true );

  for( auto scene : this->scenes )
  {
    CameraHelper::setAspectRatio( &*scene->getCamera(), cached_data.width / cached_data.height );
  }

  this->dirty = false;
}