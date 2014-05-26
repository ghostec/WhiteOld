#include "Renderer/ModelInstance.h"

ModelInstance::ModelInstance( ModelAsset* model_asset )
{
  static int id = 1;
  this->model_asset = model_asset;
  this->picking_id = id++;
}

void ModelInstance::setModelAsset( ModelAsset* model_asset )
{
  this->model_asset = model_asset;
}

void ModelInstance::addShader( Shader* shader )
{
  this->shaders.push_back( shader );
  this->model_asset->configureShader( shader );
}

void ModelInstance::updateTransform( std::vector< Shader* >* shaders )
{
  for( Shader* shader : *shaders )
  {
    shader->setUniformMatrix4fv(  "Model",
                                  WMath::value_ptr( &this->transform ),
                                  GL_TRUE );
    shader->setUniform3f( "color", this->color[0], this->color[1], this->color[2] );
  }
}

void ModelInstance::draw()
{
  this->updateTransform( this->model_asset->getShaders() );
  this->updateTransform( &this->shaders );
  this->model_asset->draw( &this->shaders );
}

void ModelInstance::setColor( WMath::vec3 color )
{
  this->color = color;
}