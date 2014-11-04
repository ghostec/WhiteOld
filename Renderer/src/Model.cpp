#include "Renderer/Model.h"

Model::Model( std::string name, std::shared_ptr<Mesh> mesh, ModelType model_type )
{
  this->name = name;
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
