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

class SceneGraph
{
  private:
    std::shared_ptr<SGNode> root_node;
  public:
    SceneGraph();
    void addSGNode( std::shared_ptr<SGNode> sg_node );
    void removeSGNode( std::string name );
    std::shared_ptr<SGNode> getRootSGNode() { return this->root_node; }
    std::shared_ptr<SGNode> findSGNode( std::string name );
};

#endif
