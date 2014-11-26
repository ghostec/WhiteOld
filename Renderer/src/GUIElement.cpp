#include "Renderer/GUIElement.h"

GUIElement::GUIElement( std::string name, ContainableData data ) : Containable( data )
{
  if( data.mode == CONTAINABLE_MODE_HSPLIT ||
    data.mode == CONTAINABLE_MODE_VSPLIT )
  {
    this->sg_node.reset( new SGNode( name, nullptr ) );
  }
  else
  {
    std::shared_ptr<Mesh> mesh( new Mesh( "gui.obj" ) );
    std::shared_ptr<Material> material( new Material() );
    material->activateColor( false );
    material->activateTexture( false );
    std::shared_ptr<Shader> shader( new Shader( "gui" ) );

    this->model.reset( new Model( "gui_model", mesh, MODEL_2D ) );
    this->model->setMaterial( material );
    this->model->setShader( shader );

    this->sg_node.reset( new SGNode( name, this->model ) );
  }
}

// Left/Child order DOES matter. Fix! (draw order)

void GUIElement::setLeftChild( std::shared_ptr<GUIElement> child )
{
  Containable<GUIElement>::setLeftChild( child );
  this->sg_node->addChild( child->getSGNode() );    
}

void GUIElement::setRightChild( std::shared_ptr<GUIElement> child )
{
  Containable<GUIElement>::setRightChild( child );
  this->sg_node->addChild( child->getSGNode() );
}

void GUIElement::setShader( std::shared_ptr<Shader> shader )
{
  this->model->setShader( shader );
}