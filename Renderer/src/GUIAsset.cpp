#include "Renderer/GUIAsset.h"

GUIAsset::GUIAsset( float width, float height, Texture* texture )
{
  float parent_width = 800;
  float parent_height = 600;

  this->shader = new Shader( "gui" );

  this->model_assets[GUI_NORMAL] = new ModelAsset( "../assets/models/square.obj" );
  this->model_assets[GUI_NORMAL]->addShader( this->shader );
  this->model_assets[GUI_NORMAL]->setTexture( texture );

  this->model_assets[GUI_HOVER] = new ModelAsset( "../assets/models/square.obj" );
  this->model_assets[GUI_HOVER]->addShader( this->shader );
  this->model_assets[GUI_HOVER]->setTexture( texture );
}

ModelAsset* GUIAsset::getModelAsset( GUI_STATE state )
{
  return this->model_assets[state];
}