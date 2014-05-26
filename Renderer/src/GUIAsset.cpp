#include "Renderer/GUIAsset.h"

GUIAsset::GUIAsset( float width, float height )
{
  float parent_width = 800;
  float parent_height = 600;

  this->model_asset = new ModelAsset( "../assets/models/square.obj" );
  this->shader = new Shader( "gui" );
  this->model_asset->addShader( this->shader );
  this->model_asset->setTexture( "diamond.png", this->shader );
}