#include "Renderer/GUIElement.h"

GUIElement::GUIElement( ContainableData data ) : Containable( data )
{
  std::shared_ptr<Mesh> mesh( new Mesh( "gui.obj" ) );
  std::shared_ptr<Texture> texture( new Texture( "diamond.png" ) );
  std::shared_ptr<Shader> shader( new Shader( "gui" ) );

  this->model.reset( new Model( "gui_model", mesh, MODEL_2D ) );
  this->model->setTexture( texture );
  this->model->setShader( shader );

  this->sg_node.reset( new SGNode( "gui_sg_node", this->model ) );
}

void GUIElement::setLeftChild( std::shared_ptr<GUIElement> child )
{
  this->sg_node->addChild( child->getSGNode() );
}

void GUIElement::setShader( std::shared_ptr<Shader> shader )
{
  this->model->setShader( shader );
}

void GUIElement::setTexture( std::shared_ptr<Texture> texture )
{
  this->model->setTexture( texture );
}
