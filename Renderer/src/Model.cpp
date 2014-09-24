#include "Renderer/Model.h"

Model::Model( std::shared_ptr<Mesh> mesh, ModelType model_type )
{
  static int id = 1;
  this->mesh = mesh;
  this->model_data.reset( new ModelData );
  this->model_type = model_type;
}

void Model::setShader( std::shared_ptr<Shader> shader )
{
  this->shader = shader;
  ShaderHelper::setVertexData( &*shader, &*this->mesh );
}

void Model::setTransform( WMath::mat4* t )
{
  this->shader->setUniform( "Model", t, GL_TRUE );
}

void Model::use()
{
  //this->shader->setUniform( "Model", this->getTransformM( ), GL_TRUE );
  if( this->texture ) this->texture->use( this->shader );
  ShaderHelper::setModelData( &*this->shader, &*this->model_data );
}

void Model::unuse()
{
  if( this->texture ) this->texture->unuse();
}

WMath::vec3 Model::getDimensions()
{
  return WMath::vec3
    ( this->scale * WMath::vec4( this->mesh->getDimensions(), 1.0 ) );
}

WMath::mat4* Model::getTransformM()
{
  this->transform = this->scale * this->rotate * this->translate;
  return &this->transform;
}

void Model::resetTransform()
{
  WMath::mat4 m; 
  transform = scale = rotate = translate = m;
}