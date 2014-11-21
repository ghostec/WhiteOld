#include "Renderer/Model.h"

Model::Model( std::string name, std::shared_ptr<Mesh> mesh, ModelType model_type )
{
  this->name = name;
  this->mesh = mesh;
  this->model_type = model_type;
  this->model_data.reset( new ModelData() );
}

void Model::setShader( std::shared_ptr<Shader> shader )
{
  this->shader = shader;
  ShaderHelper::setMesh( &*shader, &*this->mesh );
}

void Model::use()
{
  ShaderHelper::setMesh( &*shader, &*this->mesh );
  this->mesh->use();
  if( this->material ) this->material->use();
  ShaderHelper::setModelData( &*this->shader, &*this->model_data );
}

void Model::unuse()
{
  if( this->material ) this->material->unuse();
  this->mesh->unuse();
}
