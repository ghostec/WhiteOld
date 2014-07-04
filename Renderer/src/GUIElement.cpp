#include "Renderer/GUIElement.h"

GUIElement::GUIElement
  ( float width, float height, float offset_x, float offset_y,
  float offset_x_percent, float offset_y_percent )
{
  this->width = width;
  this->height = height;
  float ar = 1.0f;
  float percent = 1.0f;
  float parent_width = 800.0f;
  float parent_height = 600.0f;
  offset_x_percent = ( 1.0 / ar ) * offset_x_percent * parent_width;
  offset_y_percent = offset_y_percent * parent_height;

  std::shared_ptr<Mesh> mesh( new Mesh( "square.obj" ) );
  this->model.reset( new Model( mesh, MODEL_2D ) );

  WMath::scale( this->model->getScaleM( ),
                WMath::vec3( ( 1.0f / ar ) * percent, percent, 1.0f ) );
  WMath::translate( this->model->getTranslateM( ),
                    WMath::vec3( -1.0f + ( width + 2.0f*offset_x + 2.0f*offset_x_percent ) / parent_width,
                    1.0f - ( height + 2.0f*offset_y + 2.0f*offset_y_percent ) / parent_height,
                    0.0f ) );
}

GUIElement::GUIElement
  ( std::shared_ptr<GUIElement> parent,
  float percent, float offset_x, float offset_y,
  float offset_x_percent, float offset_y_percent )
{
  float parent_width = parent->getWidth();
  float parent_height = parent->getHeight();

  float ar = parent_width / parent_height;

  this->width = ( 1.0f / ar ) * percent * parent_width;
  this->height = percent * parent_height;
  offset_x_percent = ( 1.0 / ar ) * offset_x_percent * parent_width;
  offset_y_percent = offset_y_percent * parent_height;
  
  std::shared_ptr<Mesh> mesh( new Mesh( "square.obj" ) );
  this->model.reset( new Model( mesh ) );

  WMath::scale( this->model->getScaleM(),
    WMath::vec3( (1.0f / ar) * percent, percent, 1.0f ) );

  WMath::translate( this->model->getTranslateM(),
    WMath::vec3( -1.0f + ( width + 2.0f*offset_x + 2.0f*offset_x_percent ) / parent_width,
    1.0f - ( height + 2.0f*offset_y + 2.0f*offset_y_percent ) / parent_height, 
    0.0f ) );
}

void GUIElement::setState( std::string name )
{
  this->current_state = name;
  this->model->setShader( this->state[name].shader );
  this->model->setTexture( this->state[name].texture );
}

void GUIElement::setState( std::string name, GUIState state )
{
  this->current_state = name;
  this->state[name] = state;
}

void GUIElement::translate( float x, float y )
{
  float parent_width = 800.0f;
  float parent_height = 600.0f;

  WMath::translate( this->model->getTranslateM( ),
    WMath::vec3( ( 2.0f*x ) / parent_width, - ( 2.0f*y ) / parent_height, 0.0f ) );
}