#ifndef __WHITE_SCENEGRAPH__
#define __WHITE_SCENEGRAPH__

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <queue>
#include "Renderer/SGNode.h"

class SGNode;

class SceneGraph
{
  private:
    std::vector< std::shared_ptr<SGNode> > nodes;
    std::map< std::shared_ptr<Model>, int > models_map;
    std::vector< std::shared_ptr<Model> > models;
  public:
    void addModel( std::shared_ptr<Model> model );
    void removeModel( std::shared_ptr<Model> model );
    void addNode( std::shared_ptr<SGNode> node );
    void removeNode( std::shared_ptr<SGNode> node );
    std::vector< std::shared_ptr<SGNode> > getNodes() { return this->nodes; }
    std::shared_ptr<SGNode> getNode( std::string name );
    std::vector < std::shared_ptr<Model> > getModels() { return this->models; }
};

#endif
