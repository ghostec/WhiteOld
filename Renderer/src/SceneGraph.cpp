#include "Renderer/SceneGraph.h"

void SceneGraph::addModel( std::shared_ptr<Model> model )
{
  if( model == nullptr ) return;
  bool found = false;
  for( std::pair< std::shared_ptr<Model>, int> m : this->models_map )
  {
    if( m.first == model )
    {
      m.second += 1; found = true; break;
      if( m.second == 1 ) this->models.push_back( model );
    }
  }
  if( !found )
  {
    this->models_map[model] = 1;
    this->models.push_back( model );
  }
}

void SceneGraph::removeModel( std::shared_ptr<Model> model )
{
  if( model == nullptr ) return;
  bool remove = false;
  for( std::pair< std::shared_ptr<Model>, int> m : this->models_map )
  {
    if( m.first == model )
    {
      m.second -= 1;
      if( m.second == 0 ) remove = true;
      break;
    }
  }
  if( remove )
  {
    this->models.erase( std::remove_if( this->models.begin( ), this->models.end( ),
      [&] ( std::shared_ptr<Model>& m ){ return m == model; } ), this->models.end( ) );
  }
}

void SceneGraph::addNode( std::shared_ptr<SGNode> node )
{
  this->nodes.push_back( node );
  this->addModel( node->getModel() );
  node->setSceneGraph( this );
}

void SceneGraph::removeNode( std::shared_ptr<SGNode> node )
{
  this->nodes.erase( std::remove_if( this->nodes.begin( ), this->nodes.end( ),
    [&] ( std::shared_ptr<SGNode>& n ){ return n == node; } ), this->nodes.end( ) );

  this->removeModel( node->getModel( ) );
}

std::shared_ptr<SGNode> SceneGraph::getNode( std::string name )
{
  std::queue< std::shared_ptr<SGNode> > q;
  std::vector< std::shared_ptr<SGNode> > v;
  q.push( this->nodes[0] ); v.push_back( this->nodes[0] );

  if( strcmp( this->nodes[0]->getName( ).c_str( ), name.c_str( ) ) == 0 ) return this->nodes[0];

  while( !q.empty() )
  {
    std::shared_ptr<SGNode> n = q.front(); q.pop();
    
    for( std::shared_ptr<SGNode> c : n->getChildren() )
    {
      if( strcmp( c->getName().c_str(), name.c_str() ) == 0 ) return c;
      if( std::find( v.begin(), v.end(), c ) == v.end() )
      {
        v.push_back(c); q.push(c);
      }
    }
  }
}