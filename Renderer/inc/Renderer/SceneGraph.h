#ifndef __WHITE_SCENEGRAPH__
#define __WHITE_SCENEGRAPH__

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <string>
#include "Renderer/SGNode.h"

class SceneGraph
{
  private:
    std::vector< std::shared_ptr<SGNode> > nodes;
  public:
    void addNode( std::shared_ptr<SGNode> node );
    std::vector< std::shared_ptr<SGNode> > getNodes() { return this->nodes; }
    std::shared_ptr<SGNode> getNode( std::string name );
};

#endif
