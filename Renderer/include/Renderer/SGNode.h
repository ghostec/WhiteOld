#ifndef __WHITE_SGNODE__
#define __WHITE_SGNODE__

#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <memory>
#include <string>
#include "Model.h"
#include "WMath/WMath.h"

struct SGNodeTransformData
{
  SGNodeTransformData() : scale(1) {};
  WMath::vec3 position, scale;
  WMath::quaternion rotate;
};

struct SGNodeWorldTransform
{
  SGNodeTransformData data;
  WMath::mat4 transform;
};

struct SGNodePropagation
{
  SGNodeTransformData t_path, t_node;
};

typedef enum _PropagationType
{
  NORMAL
} PropagationType;

class SGNode
{
  private:
    std::string name;
    std::shared_ptr<Model> model;
    std::vector< std::shared_ptr<SGNode> > children;
    SGNodeWorldTransform world_transform;
    bool world_transform_dirty;
    SGNodePropagation propagation;
  public:
    SGNode( std::string name, std::shared_ptr<Model> model );
    void addChild( std::shared_ptr<SGNode> child );
    void removeChild( std::string name );
    //getters
    WMath::vec3 getDimensions();
    std::string getName() { return this->name; }
    bool isWorldTransformDirty() { return this->world_transform_dirty; }
    SGNodeWorldTransform getWorldTransform() { return this->world_transform; }
    WMath::mat4 getWorldTransformM() { return this->world_transform.transform; }
    std::shared_ptr<Model> getModel() { return this->model; }
    SGNodePropagation getPropagation() { return this->propagation; }
    std::vector< std::shared_ptr<SGNode> > getChildren()
      { return this->children; }
    //setters
    void setWorldTransformDirty( bool v );
    void setWorldTransform( SGNodeWorldTransform world_transform );
    void setWorldTransform( WMath::mat4 world_transform );
    void setModel( std::shared_ptr<Model> model );
    void setPropagation( SGNodePropagation p ) { this->propagation = p; }
};

class SGNodeIterator
{
  private:
    std::queue< SGNode* > bfs_q;
    std::vector< SGNode* > bfs_v;
  public:
    SGNodeIterator( SGNode* root );
    SGNode* begin();
    SGNode* next();
};

#endif
