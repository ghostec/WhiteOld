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
  return WMath::vec3( WMath::scaleM( this->world_transform.scale )
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
