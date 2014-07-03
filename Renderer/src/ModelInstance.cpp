#include "Renderer/ModelInstance.h"

ModelInstance::ModelInstance( std::shared_ptr<ModelAsset> model_asset )
{
  static int id = 1;
  this->model_asset = model_asset;
  this->picking_id = id++;
}

void ModelInstance::setShader( std::shared_ptr<Shader> shader )
{
  this->shader = shader;
  this->model_asset->configureShader( shader );
}

void ModelInstance::updateTransform( std::shared_ptr<Shader> shader )
{
  shader->setUniform(  "Model", this->getTransformM(),
    GL_TRUE );
}

void ModelInstance::addFloat( std::string name, float f )
{
  this->data.floats.push_back( std::make_pair( name, f ) );
}

void ModelInstance::draw()
{
  this->updateTransform( this->shader );
  this->model_asset->draw( this->shader );
}

WMath::mat4* ModelInstance::getTransformM( )
{
  this->transform = this->scale * this->rotate * this->translate;
  return &this->transform;
}