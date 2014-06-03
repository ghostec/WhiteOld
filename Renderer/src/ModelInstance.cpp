#include "Renderer/ModelInstance.h"

ModelInstance::ModelInstance( std::shared_ptr<ModelAsset> model_asset )
{
  static int id = 1;
  this->model_asset = model_asset;
  this->picking_id = id++;
  this->opacity = 1.0f;
}

void ModelInstance::addShader( std::shared_ptr<Shader> shader )
{
  this->shaders.push_back( shader );
  this->model_asset->configureShader( shader );
}

void ModelInstance::updateTransform( std::vector< std::shared_ptr<Shader> >* shaders )
{
  for( std::shared_ptr<Shader> shader : *shaders )
  {
    shader->setUniformMatrix4fv(  "Model",
                                  WMath::value_ptr( this->getTransformM() ),
                                  GL_TRUE );
    shader->setUniform3f( "color", this->color[0], this->color[1], this->color[2] );
  }
}

void ModelInstance::updateOpacity( std::vector< std::shared_ptr<Shader> >* shaders )
{
  for( std::shared_ptr<Shader> shader : *shaders )
  {
    shader->setUniform1f( "opacity", this->opacity );
  }
}

void ModelInstance::draw()
{
  this->updateTransform( this->model_asset->getShaders() );
  this->updateTransform( &this->shaders );
  this->updateOpacity( this->model_asset->getShaders() );
  this->updateOpacity( &this->shaders );
  this->model_asset->draw( &this->shaders );
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