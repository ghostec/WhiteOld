#include "Renderer/SGNode.h"

void SGNode::addChild( std::shared_ptr<SGNode> child )
{
  this->children.push_back( child );
}