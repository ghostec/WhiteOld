#include "Renderer/GUIInstance.h"

GUIInstance::GUIInstance( GUIAsset* gui_asset, float width, float height )
{
  this->width = width;
  this->height = height;
  float ar = 1.0f;
  float percent = 1.0f;
  float parent_width = 800.0f;
  float parent_height = 600.0f;

  this->model_instance = new ModelInstance( gui_asset->getModelAsset( GUI_NORMAL ) );
  WMath::scale( this->model_instance->getTransform( ),
                WMath::vec3( ( 1.0f / ar ) * percent, percent, 1.0f ) );
  WMath::translate( this->model_instance->getTransform( ),
                WMath::vec3( -1.0f + width / parent_width, 1.0f - height / parent_height, 0.0f ) );
}

GUIInstance::GUIInstance( GUIAsset* gui_asset, GUIInstance* parent, float percent )
{
  this->gui_asset = gui_asset;

  float parent_width = parent->getWidth();
  float parent_height = parent->getHeight();

  float ar = parent_width / parent_height;

  this->width = ( 1.0f / ar ) * percent * parent_width;
  this->height = percent * parent_height;

  float offset_x = 20.0f;
  float offset_y = 20.0f;
  
  this->model_instance = new ModelInstance( gui_asset->getModelAsset( GUI_NORMAL ) );
  WMath::scale( this->model_instance->getTransform(), 
                WMath::vec3( (1.0f / ar) * percent, percent, 1.0f ) );
  WMath::translate( this->model_instance->getTransform(),
                    WMath::vec3( -1.0f + (width+2.0f*offset_x) / parent_width, 1.0f - (height+2.0f*offset_y) / parent_height, 0.0f ) );
}

void GUIInstance::setState( GUI_STATE state )
{
  this->model_instance->setModelAsset( this->gui_asset->getModelAsset( state ) );
}

void GUIInstance::translate( float x, float y )
{
  float parent_width = 800.0f;
  float parent_height = 600.0f;

  WMath::translate( this->model_instance->getTransform( ),
                    WMath::vec3( ( 2.0f*x ) / parent_width, - ( 2.0f*y ) / parent_height, 0.0f ) );
}