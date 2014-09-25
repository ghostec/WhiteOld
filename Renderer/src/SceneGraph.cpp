#include "Renderer/SceneGraph.h"

void SceneGraph::addNode( std::shared_ptr<SGNode> node )
{
  this->nodes.push_back( node );
}

std::shared_ptr<SGNode> SceneGraph::getNode( std::string name )
{
  // TODO: depth
  for( std::shared_ptr<SGNode> sg_node : this->nodes )
  {
    if( sg_node->getName() == name ) return sg_node;
  }
}