#include "Renderer/ModelInstance.h"

ModelInstance::ModelInstance( std::shared_ptr<Mesh> mesh )
{
  static int id = 1;
  this->mesh = mesh;
  this->model_data.reset( new ModelData );
}

void ModelInstance::setShader( std::shared_ptr<Shader> shader )
{
  this->shader = shader;
  this->mesh->configureShader( shader );
}

void ModelInstance::update()
{
  this->shader->setUniform( "Model", this->getTransformM(), GL_TRUE );
  this->texture->use( this->shader );
  ShaderHelper::setModelData( &*this->shader, &*this->model_data );
}

WMath::mat4* ModelInstance::getTransformM( )
{
  this->transform = this->scale * this->rotate * this->translate;
  return &this->transform;
}