#include "Renderer/SceneGraph.h"

SceneGraph::SceneGraph()
{
  this->root_node.reset( new SGNode( "root", nullptr ) );
}

void SceneGraph::addSGNode( std::shared_ptr<SGNode> sg_node )
{
  this->root_node->addChild( sg_node );
}

void SceneGraph::removeSGNode( std::string name )
{
  this->root_node->removeChild( name );
}

std::shared_ptr<SGNode> SceneGraph::findSGNode( std::string name )
{
  std::queue< std::shared_ptr<SGNode> > bfs_q;
  std::vector< std::shared_ptr<SGNode> > bfs_v;

  bfs_q.push( this->root_node );
  bfs_v.push_back( this->root_node );

  while( !bfs_q.empty( ) )
  {
    std::shared_ptr<SGNode> n = bfs_q.front( ); bfs_q.pop( );
    std::shared_ptr<Model> model = n->getModel( );

    if( n->getName() == name ) return n;

    for( auto c : n->getChildren( ) )
    {
      if( std::find( bfs_v.begin( ), bfs_v.end( ), c ) == bfs_v.end( ) )
      {
        bfs_q.push( c ); bfs_v.push_back( c );
      }
    }
  }

  return nullptr;
}