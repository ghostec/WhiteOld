#include "Renderer/SceneGraph.h"

void SceneGraph::addNode( std::shared_ptr<SGNode> node )
{
  this->nodes.push_back( node );
}