#include "Renderer/Scene.h"

void Scene::draw()
{
  //GLuint light_index = glGetUniformBlockIndex( program, "LightBlock" );
  //glUniformBlockBinding( program, light_index, 0 );
  //glBindBuffer( GL_UNIFORM_BUFFER, light_buffer );
  //glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeof(LightBlock), &Light );

  int vector_models_size = this->model_instances.size();
  for( int i = 0; i < vector_models_size; i++ )
  {
    this->model_instances.at(i)->move();
    this->model_instances.at(i)->draw();
  }
}

void Scene::addModel( ModelInstance* model_instance )
{
  bool found_asset = false;
  for( ModelAssetPair model_asset_pair : this->model_assets )
  {
    if( model_asset_pair.second == model_instance->getModelAsset( ) )
    {
      this->model_instances.push_back( model_instance );
      model_asset_pair.first += 1;
      found_asset = true;
      break;
    }
  }
  if( !found_asset )
  {
    this->model_instances.push_back( model_instance );
    model_assets.push_back( std::make_pair( 1, 
                                            model_instance->getModelAsset( ) )
                          );
  }
}

void Scene::addLight( Light* light )
{
  this->lights.push_back( light );
  light->registerObserver(  "DIRTY",
                            std::bind( &Scene::updateLights, this ),
                            "SCENE" );
  this->updateLights();
}

void Scene::updateLightsForShaders( std::vector< Shader* >* shaders )
{
  for( Shader* shader : *shaders )
    shader->setLight( this->lights[0] );
}

void Scene::updateLights()
{
  for( const ModelAssetPair model_asset_pair : this->model_assets )
    this->updateLightsForShaders( model_asset_pair.second->getShaders() );
  for( ModelInstance* model_instance : this->model_instances )
    this->updateLightsForShaders( model_instance->getShaders() );
}

void Scene::setCamera( Camera* camera )
{
  // TODO: If this->camera != null, unregister old camera.
  this->camera  = camera;
  this->camera->registerObserver( "DIRTY",
                                  std::bind( &Scene::updateCamera, this ),
                                  "SCENE" );
  this->updateCamera();
}

void Scene::updateCameraForShaders( std::vector< Shader* >* shaders )
{
  for( Shader* shader : *shaders )
    shader->setCamera( this->camera );
}

void Scene::updateCamera()
{
  for( const ModelAssetPair model_asset_pair : this->model_assets )
    this->updateCameraForShaders( model_asset_pair.second->getShaders() );
  for( ModelInstance* model_instance : this->model_instances )
    this->updateCameraForShaders( model_instance->getShaders() );
}