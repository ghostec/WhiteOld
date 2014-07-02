#include "Renderer/ModelInstance.h"

ModelInstance::ModelInstance( std::shared_ptr<ModelAsset> model_asset )
{
  static int id = 1;
  this->model_asset = model_asset;
  this->picking_id = id++;
  this->opacity = 1.0f;
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
  shader->setUniform( "color", this->color.vec );
}

void ModelInstance::updateOpacity( std::shared_ptr<Shader> shader )
{
  shader->setUniform( "opacity", this->opacity );
}

void ModelInstance::draw()
{
  this->updateTransform( this->shader );
  this->updateOpacity( this->shader );
  this->model_asset->draw( this->shader );
}

void ModelInstance::setColor( WMath::vec3 color )
{
  this->color = color;
}

void ModelInstance::setOpacity( float opacity )
{
  this->opacity = opacity;
}

WMath::mat4* ModelInstance::getTransformM( )
{
  this->transform = this->scale * this->rotate * this->translate;
  return &this->transform;
}