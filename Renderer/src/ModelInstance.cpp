#include "Renderer/ModelInstance.h"

ModelInstance::ModelInstance( ModelAsset* model_asset )
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
  }
}

void ModelInstance::draw()
{
  this->updateTransform( this->model_asset->getShaders() );
  this->updateTransform( &this->shaders );
  this->model_asset->draw( &this->shaders );
}

void ModelInstance::move( )
{
  if( this->moves.ARROW_UP )
    WMath::translate( &this->transform, WMath::vec3( 0.0f, 0.005f, 0.0f ) );
  if( this->moves.ARROW_DOWN )
    WMath::translate( &this->transform, WMath::vec3( 0.0f, -0.005f, 0.0f ) );
}