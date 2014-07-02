#include "Renderer/GUIAsset.h"

GUIAsset::GUIAsset
  ( float width, float height, std::shared_ptr<Texture> texture )
{
  float parent_width = 800;
  float parent_height = 600;

  this->shader.reset( new Shader( "gui" ) );

  this->model_assets[GUI_NORMAL].reset
    ( new ModelAsset( "square.obj", MODEL_ASSET_2D ) );
  //this->model_assets[GUI_NORMAL]->setShader( this->shader );
  this->model_assets[GUI_NORMAL]->setTexture( texture );

  this->model_assets[GUI_HOVER].reset
    ( new ModelAsset( "square.obj", MODEL_ASSET_2D ) );
  //this->model_assets[GUI_HOVER]->setShader( this->shader );
  this->model_assets[GUI_HOVER]->setTexture( texture );
}

std::shared_ptr<ModelAsset> GUIAsset::getModelAsset( GUI_STATE state )
{
  return this->model_assets[state];
}