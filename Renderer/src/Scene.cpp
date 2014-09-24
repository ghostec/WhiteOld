#include "Renderer/Scene.h"

Scene::Scene( std::string name )
{
  this->name = name;
  this->camera.reset( new Camera() );
}

void Scene::update()
{
  if( this->camera )
  {
    this->updateCamera();
    this->camera->setDirty( false );
  }
  if( this->lights.size() > 0 )
  {
    this->updateLights();
    this->lights[0].setDirty( false );
  }
}

void Scene::addModel( std::shared_ptr<Model> model_instance )
{
  this->models.push_back( model_instance );
}

void Scene::removeModel( std::shared_ptr<Model> model )
{
  this->models.erase( std::remove_if( this->models.begin(), this->models.end(),
    [&]( std::shared_ptr<Model>& m ){ return m == model; } ), this->models.end() );
}

void Scene::addLight( Light light )
{
  this->lights.push_back( light );
}

void Scene::updateLightsForShader( std::shared_ptr<Shader> shader )
{
  ShaderHelper::setLight( &*shader, &this->lights[0] );
}

void Scene::updateLights()
{
  for( std::shared_ptr<Model> model_instance : this->models )
    this->updateLightsForShader( model_instance->getShader() );
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

void Scene::setCamera( std::shared_ptr<Camera> camera )
{
  this->camera = camera;
  std::string text = this->name + "_camera";
  active_window->registerObserver
    ( "RESIZE", std::bind( CameraHelper::updateWindow, &*camera ), text );
}

void Scene::setSceneGraph( std::shared_ptr<SceneGraph> scene_graph )
{
  this->scene_graph = scene_graph;
}