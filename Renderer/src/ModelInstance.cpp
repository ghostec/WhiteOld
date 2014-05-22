#include "Renderer/ModelInstance.h"

ModelInstance::ModelInstance( ModelAsset* model_asset, GLenum DRAW_MODE )
{
  this->model_asset = model_asset;
  this->DRAW_MODE = DRAW_MODE;
}

void ModelInstance::draw()
{
  this->model_asset->getShader()->setUniformMatrix4fv(  "Model", 
                                                        WMath::value_ptr(
                                                          &this->transform ),
                                                        GL_TRUE );
  this->model_asset->draw( DRAW_MODE );
}

void ModelInstance::move( )
{
  if( this->moves.ARROW_UP )
    WMath::translate( &this->transform, WMath::vec3( 0.0f, 0.005f, 0.0f ) );
  if( this->moves.ARROW_DOWN )
    WMath::translate( &this->transform, WMath::vec3( 0.0f, -0.005f, 0.0f ) );
}