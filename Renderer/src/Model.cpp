#include "Renderer/Model.h"

Model::Model( std::string name, std::shared_ptr<Mesh> mesh, ModelType model_type )
{
  this->name = name;
  this->mesh = mesh;
  this->model_type = model_type;
}

void Model::setShader( std::shared_ptr<Shader> shader )
{
  this->shader = shader;
  ShaderHelper::setMesh( &*shader, &*this->mesh );
}

void Model::use()
{
  this->mesh->use();
  if( this->texture ) this->texture->use( this->shader );
  ShaderHelper::setModelData( &*this->shader, &*this->model_data );
}

void Model::unuse()
{
  if( this->texture ) this->texture->unuse();
  this->mesh->unuse();
}
