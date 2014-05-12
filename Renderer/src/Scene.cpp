#include "Renderer/Scene.h"

Scene::Scene()
{
  this->proj = WMath::OpenGlPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
}

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
    this->models.at(i)->setView( this->view );
    this->models.at(i)->setProj( &this->proj );
    this->models.at(i)->draw();
  }
}

void Scene::addModel( Model* model )
{
  this->models.push_back( model );
}

void Scene::setCamera( Camera* camera )
{
  this->camera  = camera;
  this->view    = camera->getView();
}