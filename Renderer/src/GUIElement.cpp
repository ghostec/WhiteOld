#include "Renderer/GUIElement.h"

GUIElement::GUIElement
  ( std::shared_ptr<Mesh> mesh, std::shared_ptr<GUIElement> parent,
  GUIType gui_type )
{
  this->model.reset( new Model( "gui", mesh ) );
  this->parent = parent;
  this->gui_type = gui_type;
  this->ratio = this->parent_percent = 1.0f;
  this->offset = this->offset_percent = WMath::vec2(0);
  this->dirty = true;
}

void GUIElement::setOffset( WMath::vec2 offset )
{
  this->offset = offset;
  this->dirty = true;
}

void GUIElement::addOffset( WMath::vec2 offset )
{
  this->offset = this->offset + offset;
  this->dirty = true;
}

void GUIElement::setOffsetPercent( WMath::vec2 offset_percent )
{
  this->offset_percent = offset_percent;
  this->dirty = true;
}

void GUIElement::addOffsetPercent( WMath::vec2 offset_percent )
{
  this->offset_percent = this->offset_percent + offset_percent;
  this->dirty = true;
}

void GUIElement::setParentPercent( float parent_percent )
{
  this->parent_percent = parent_percent;
  this->dirty = true;
}

void GUIElement::addParentPercent( float parent_percent )
{
  this->parent_percent = this->parent_percent+ parent_percent;
  this->dirty = true;
}

void GUIElement::addChild( std::shared_ptr<GUIElement> child )
{
  this->child.push_back( child );
}

float GUIElement::getPropagatedParentPercent()
{
  std::shared_ptr<GUIElement> next_parent = this->parent;
  float parent_percent = this->parent_percent;
  while( next_parent )
  {
    parent_percent *= next_parent->parent_percent;
    next_parent = next_parent->getParent();
  }
  return parent_percent;
}

float GUIElement::getPropagatedAR()
{
  std::shared_ptr<GUIElement> next_parent = this->parent;
  float ar = 1.0f;
  while( next_parent )
  {
    WMath::vec2 parent_dimensions = next_parent->getDimensions();
    float parent_ar = parent_dimensions[0] / parent_dimensions[1];
    ar *= parent_ar;
    next_parent = next_parent->getParent( );
  }
  return ar * 0.75;
}

void GUIElement::update()
{
  WMath::vec2 parent_dimensions;
  if( this->parent )
    parent_dimensions = this->parent->getDimensions();
  else
    parent_dimensions = WMath::vec2( 800, 600 );
  
  float parent_ar = getPropagatedAR();
  float parent_percent = getPropagatedParentPercent();

  this->dimensions[0] =
    ( 1.0f / parent_ar ) * parent_percent * parent_dimensions[0];
  this->dimensions[1] = parent_percent * parent_dimensions[1];

  if( ratio > 1.0f ) this->dimensions[1] /= ratio;
  else this->dimensions[0] *= ratio;

  WMath::vec2 tmp_offset_percent;
  tmp_offset_percent[0] =
    ( 1.0 / parent_ar ) * this->offset_percent[0] * parent_dimensions[0];
  tmp_offset_percent[1] = this->offset_percent[1] * parent_dimensions[1];

  this->model->resetTransform();

  float scaleX = ( 1.0f / parent_ar ) * parent_percent;
  float scaleY = parent_percent;

  if( ratio > 1.0f ) scaleY /= ratio;
  else scaleX *= ratio;

  WMath::scale( this->model->getScaleM( ),
    WMath::vec3(
    scaleX, scaleY, 1.0f ) );

  WMath::translate( this->model->getTranslateM( ),
    WMath::vec3
    ( -1.0f + ( dimensions[0] + 2.0f*offset[0] + 2.0f*tmp_offset_percent[0] )
    / parent_dimensions[0],
    1.0f - ( dimensions[1] + 2.0f*offset[1] + 2.0f*tmp_offset_percent[1] )
    / parent_dimensions[1],
    0.0f ) );

  for( std::shared_ptr<GUIElement> child : this->child ) child->update();

  this->dirty = false;
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