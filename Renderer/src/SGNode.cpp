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

void SGNode::removeChild( std::string name )
{
  this->children.erase( std::remove_if( this->children.begin(), this->children.end(),
    [&] ( std::shared_ptr<SGNode>& n ){ return n->getName() == name; } ), this->children.end() );
}

void SGNode::setModel( std::shared_ptr<Model> model )
{
  this->model = model;
}

WMath::vec3 SGNode::getDimensions()
{
  return WMath::vec3( WMath::scaleM( this->world_transform.data.scale )
      * WMath::vec4( this->model->getMesh()->getDimensions(), 1.0 ) );
}

void SGNode::setWorldTransformDirty( bool v )
{
  if( !v ) this->world_transform_dirty = v;
  else
  {
    this->world_transform_dirty = v;
    for( auto c : this->children ) setWorldTransformDirty( v );
  }
}

void SGNode::setWorldTransform( SGNodeWorldTransform world_transform )
{
  setWorldTransformDirty( true );
  this->world_transform = world_transform;
}

void SGNode::setWorldTransform( WMath::mat4 world_transform )
{
  setWorldTransformDirty( false );
  this->world_transform.transform = world_transform;
}

SGNodeIterator::SGNodeIterator( SGNode* root )
{
  bfs_q.push( root );
  bfs_v.push_back( root );
}

SGNode* SGNodeIterator::begin() { return this->next(); }

SGNode* SGNodeIterator::next()
{
  if( bfs_q.empty() ) return nullptr;
  SGNode* n = bfs_q.front(); bfs_q.pop();

  if( n->isWorldTransformDirty() )
  {
    SGNodeWorldTransform w = n->getWorldTransform();
    SGNodePropagation pr = n->getPropagation();

    pr.t_node.position = pr.t_node.position + w.data.position;
    pr.t_node.scale = w.data.scale;
    pr.t_node.rotate = pr.t_node.rotate * w.data.rotate;

    WMath::mat4 t = WMath::scaleM( pr.t_node.scale )
      * WMath::rotateM( pr.t_node.rotate )
      * WMath::translateM( pr.t_node.position );
    n->setWorldTransform( t );

    for( auto c : n->getChildren() ) c->setPropagation( pr );

    n->setWorldTransformDirty( false );
  }

  for( auto c : n->getChildren( ) )
  {
    if( std::find( bfs_v.begin(), bfs_v.end(), &*c ) == bfs_v.end() )
    {
      bfs_q.push( &*c ); bfs_v.push_back( &*c );
    }
  }

  return n;
}
