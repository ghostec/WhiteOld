#include "Renderer/Scene.h"

void Scene::draw()
{
  if( this->camera->getDirty() == true )
  {
    this->updateCamera();
    this->camera->setDirty( false );
  }
  if( this->lights[0]->getDirty( ) == true )
  {
    this->updateLights();
    this->lights[0]->setDirty( false );
  }
  for( std::shared_ptr<ModelInstance> model_instance : this->model_instances )
    model_instance->draw();
}

void Scene::addModel( std::shared_ptr<ModelInstance> model_instance )
{
  this->model_instances.push_back( model_instance );
  if( this->model_assets.find( model_instance->getModelAsset() ) 
      == this->model_assets.end() )
    this->model_assets[model_instance->getModelAsset( )] = 1;
  else
    this->model_assets[model_instance->getModelAsset( )] += 1;
}

void Scene::addLight( std::shared_ptr<Light> light )
{
  this->lights.push_back( light );
}

void Scene::updateLightsForShaders( std::shared_ptr< std::vector< std::shared_ptr<Shader> > > shaders )
{
  for( std::shared_ptr<Shader> shader : *shaders )
  {
    ShaderHelper::setLight( shader, this->lights[0] );
  }
}

void Scene::updateLights()
{
  for( std::map< std::shared_ptr<ModelAsset>, int >::iterator it 
        = this->model_assets.begin();
        it != this->model_assets.end(); it++ )
    this->updateLightsForShaders( it->first->getShaders() );
  for( std::shared_ptr<ModelInstance> model_instance : this->model_instances )
    this->updateLightsForShaders( model_instance->getShaders() );
}

void Scene::setCamera( std::shared_ptr<Camera> camera )
{
  this->camera  = camera;
}

void Scene::updateCameraForShaders
  ( std::shared_ptr< std::vector< std::shared_ptr<Shader> > > shaders )
{
  for( std::shared_ptr<Shader> shader : *shaders )
  {
    ShaderHelper::setCamera( shader, this->camera );
  }
}

void Scene::updateCamera()
{
  for( std::map< std::shared_ptr<ModelAsset>, int >::iterator it
    = this->model_assets.begin( );
    it != this->model_assets.end( ); it++ )
    this->updateCameraForShaders( it->first->getShaders() );
  for( std::shared_ptr<ModelInstance> model_instance : this->model_instances )
    this->updateCameraForShaders( model_instance->getShaders() );
}

std::shared_ptr<ModelInstance> Scene::getModelInstanceWithId( int id )
{
  for( std::shared_ptr<ModelInstance> model_instance : this->model_instances )
  {
    if( model_instance->getPickingId() == id )
      return model_instance;
  }
}