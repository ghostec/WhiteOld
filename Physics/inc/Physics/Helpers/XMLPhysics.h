#ifndef __PHYSICS_HELPERS_XMLPHYSICS__
#define __PHYSICS_HELPERS_XMLPHYSICS__

#include <iostream>
#include <memory>
#include <string>
#include "tinyxml2/tinyxml2.h"
#include "Renderer/SceneGraph.h"
#include "Renderer/SGNode.h"
#include "Physics/Body.h"
#include "Physics/PhysicsManager.h"

namespace XMLHelper
{
  void createBody( tinyxml2::XMLElement* el,
    std::shared_ptr<SceneGraph> scene_graph,
    std::shared_ptr<PhysicsManager> physics_manager );
  void importPhysics( std::string file_name,
    std::shared_ptr<SceneGraph> scene_graph,
    std::shared_ptr<PhysicsManager> physics_manager );
}

#endif