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
  this->mesh->configureShader( shader );
}

void Model::update()
{
  this->shader->setUniform( "Model", this->getTransformM(), GL_TRUE );
  this->texture->use( this->shader );
  ShaderHelper::setModelData( &*this->shader, &*this->model_data );
}

WMath::mat4* Model::getTransformM( )
{
  this->transform = this->scale * this->rotate * this->translate;
  return &this->transform;
}