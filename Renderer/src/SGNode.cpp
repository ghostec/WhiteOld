#include "Renderer/SGNode.h"

SGNode::SGNode( std::string name, std::shared_ptr<Model> model )
{
  this->name = name;
  this->model = model;
}

void SGNode::addChild( std::shared_ptr<SGNode> child )
{
  this->children.push_back( child );
}