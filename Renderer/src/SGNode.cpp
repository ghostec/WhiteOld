#include "Renderer/SGNode.h"

SGNode::SGNode( std::string name, std::shared_ptr<Model> model )
{
  this->name = name;
  this->model = model;
  this->setScale( WMath::vec3(1) );
}

void SGNode::addChild( std::shared_ptr<SGNode> child )
{
  this->children.push_back( child );
}

void SGNode::setModel( std::shared_ptr<Model> model )
{
  if( this->scene_graph )
  {
    this->scene_graph->removeModel( this->model );
    this->scene_graph->addModel( model );
  }

  this->model = model;
}