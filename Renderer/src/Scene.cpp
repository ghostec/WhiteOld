#include "Renderer/Scene.h"

void Scene::update()
{
  if( this->camera->getDirty() == true )
  {
    this->updateCamera();
    this->camera->setDirty( false );
  }
  if( this->lights[0]->getDirty() == true )
  {
    this->updateLights();
    this->lights[0]->setDirty( false );
  }
}

void Scene::addModel( std::shared_ptr<Model> model_instance )
{
  this->models.push_back( model_instance );
}

void Scene::addLight( std::shared_ptr<Light> light )
{
  this->lights.push_back( light );
}

void Scene::updateLightsForShader( std::shared_ptr<Shader> shader )
{
  ShaderHelper::setLight( &*shader, &*this->lights[0] );
}

void Scene::updateLights()
{
  for( std::shared_ptr<Model> model_instance : this->models )
    this->updateLightsForShader( model_instance->getShader() );
}

void Scene::setCamera( std::shared_ptr<Camera> camera )
{
  this->camera  = camera;
}

void Scene::updateCameraForShader( std::shared_ptr<Shader> shader )
{
  ShaderHelper::setCamera( &*shader, &*this->camera );
}

void Scene::updateCamera()
{
  for( std::shared_ptr<Model> model : this->models )
    this->updateCameraForShader( model->getShader() );
}