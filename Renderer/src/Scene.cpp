#include "Renderer/Scene.h"

void Scene::draw()
{
  //GLuint light_index = glGetUniformBlockIndex( program, "LightBlock" );
  //glUniformBlockBinding( program, light_index, 0 );
  //glBindBuffer( GL_UNIFORM_BUFFER, light_buffer );
  //glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeof(LightBlock), &Light );

  int vector_models_size = this->models.size();
  for( int i = 0; i < vector_models_size; i++ )
  {
    this->models.at(i)->move();
    this->models.at(i)->draw();
  }
}

void Scene::addModel( ModelInstance* model )
{
  this->models.push_back( model );
}

void Scene::addLight( Light* light )
{
  this->lights.push_back( light );
  light->registerObserver(  "DIRTY",
                            std::bind( &Scene::updateLights, this ),
                            "SCENE" );
  int vector_models_size = this->models.size( );
  for( int i = 0; i < vector_models_size; i++ )
  {
    this->models.at( i )->getModelAsset()->getShader()->setLight( this->lights[0] );
  }
}

void Scene::updateLights()
{
  int vector_models_size = this->models.size( );
  for( int i = 0; i < vector_models_size; i++ )
  {
    this->models.at( i )->getModelAsset( )->getShader( )->setLight( this->lights[0] );
  }
}

void Scene::setCamera( Camera* camera )
{
  // TODO: If this->camera != null, unregister old camera.
  this->camera  = camera;
  this->camera->registerObserver( "DIRTY",
                                  std::bind( &Scene::updateCamera, this ),
                                  "SCENE" );
  int vector_models_size = this->models.size( );
  for( int i = 0; i < vector_models_size; i++ )
  {
    this->models.at( i )->getModelAsset( )->getShader( )->setCamera( this->camera );
  }
}

void Scene::updateCamera()
{
  int vector_models_size = this->models.size( );
  for( int i = 0; i < vector_models_size; i++ )
  {
    this->models.at( i )->getModelAsset( )->getShader( )->setCamera( this->camera );
  }
}