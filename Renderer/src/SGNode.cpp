#include "Renderer/SGNode.h"

SGNode::SGNode( std::string name, std::shared_ptr<Model> model )
{
  this->name = name;
  this->model = model;
  this->scale = WMath::vec3(1);
  this->pivot = WMath::vec3(0);
}

void SGNode::addChild( std::shared_ptr<SGNode> child )
{
  this->children.push_back( child );
}

void SGNode::removeChild( std::string name )
{
  this->children.erase( std::remove_if( this->children.begin(), this->children.end(),
    [&] ( std::shared_ptr<SGNode>& n ){ return n->getName() == name; } ), this->children.end() );
}

void SGNode::setModel( std::shared_ptr<Model> model )
{
  this->model = model;
}