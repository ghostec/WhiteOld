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
  for( std::shared_ptr<Model> model_instance : this->scene_graph->getModels() )
    this->updateLightsForShader( model_instance->getShader() );
}

void Scene::updateCameraForShader( std::shared_ptr<Shader> shader )
{
  ShaderHelper::setCamera( &*shader, &*this->camera );
}

void Scene::updateCamera()
{
  //std::cout << this->scene_graph->getModels( ).size() << std::endl;
  for( std::shared_ptr<Model> model : this->scene_graph->getModels() )
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