#include "Renderer/GUIElement.h"

void GUIElement::constructorTail
  ( std::shared_ptr<Mesh> mesh, float ar, WMath::vec2 parent_dimensions,
  WMath::vec2 offset, WMath::vec2 offset_percent, float parent_percent )
{
  offset_percent[0] = ( 1.0 / ar ) * offset_percent[0] * parent_dimensions[0];
  offset_percent[1] = offset_percent[1] * parent_dimensions[1];

  this->model.reset( new Model( mesh ) );

  WMath::scale( this->model->getScaleM( ),
    WMath::vec3( ( 1.0f / ar ) * parent_percent, parent_percent, 1.0f ) );

  WMath::translate( this->model->getTranslateM( ),
    WMath::vec3
    ( -1.0f + ( dimensions[0] + 2.0f*offset[0] + 2.0f*offset_percent[0] )
    / parent_dimensions[0],
    1.0f - ( dimensions[1] + 2.0f*offset[1] + 2.0f*offset_percent[1] )
    / parent_dimensions[1],
    0.0f ) );
}

GUIElement::GUIElement
  ( std::shared_ptr<Mesh> mesh, std::shared_ptr<GUIElement> parent,
  float parent_percent, WMath::vec2 offset, WMath::vec2 offset_percent,
  GUIType gui_type )
{
  this->gui_type = gui_type;
  
  WMath::vec2 parent_dimensions = parent->getDimensions( );
  float ar = parent_dimensions[0] / parent_dimensions[1];
  this->dimensions[0] = ( 1.0f / ar ) * parent_percent * parent_dimensions[0];
  this->dimensions[1] = parent_percent * parent_dimensions[1];

  this->constructorTail( mesh, ar, parent_dimensions, offset,
    offset_percent, parent_percent );
}

GUIElement::GUIElement
  ( std::shared_ptr<Mesh> mesh, WMath::vec2 dimensions, WMath::vec2 offset,
  WMath::vec2 offset_percent, GUIType gui_type )
{
  this->gui_type = gui_type;

  // TODO: A manager that holds essential data (as current window dimension)
  // that can be globally accessed.
  WMath::vec2 parent_dimensions = { 800.0f, 600.0f };
  float ar = 1.0f;
  this->dimensions = dimensions;

  this->constructorTail( mesh, ar, parent_dimensions, offset,
    offset_percent, 1.0f );
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