#include "Renderer/GUIElement.h"

GUIElement::GUIElement( ContainableData data ) : Containable( data )
{
  this->mesh.reset( new Mesh( "gui.obj" ) );
  this->model.reset( new Model( "gui_model", this->mesh, MODEL_2D ) );
  this->texture.reset( new Texture( "diamond.png" ) );
  this->shader.reset( new Shader( "gui" ) );

  this->model->setTexture( this->texture );
  this->model->setShader( this->shader );

  this->sg_node.reset( new SGNode( "gui_sg_node", this->model ) );
}

void GUIElement::setShader( std::shared_ptr<Shader> shader )
{
  this->shader = shader;
  this->model->setShader( shader );
}

void GUIElement::setTexture( std::shared_ptr<Texture> texture )
{
  this->texture = texture;
  this->model->setTexture( texture );
}
