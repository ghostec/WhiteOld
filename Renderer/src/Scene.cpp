#include "Renderer/Scene.h"

void Scene::draw()
{
  //this->scene_properties.view = this->camera->getView();

  //GLuint light_index = glGetUniformBlockIndex( program, "LightBlock" );
  //glUniformBlockBinding( program, light_index, 0 );
  //glBindBuffer( GL_UNIFORM_BUFFER, light_buffer );
  //glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeof(LightBlock), &Light );

  int vector_models_size = this->models.size();
  for( int i = 0; i < vector_models_size; i++ )
  {
    this->models.at(i)->draw();
  }
}

void Scene::addModel( Model* model )
{
  this->models.push_back( model );
}

void Scene::setCamera( Camera* camera )
{
  this->camera = camera;
  //this->scene_properties.view = camera->getView();
  //this->scene_properties.proj = WMath::OpenGlPerspective( 45.0f, 800.0f / 600.0f, 0.1f, 100.0f );
}