#ifndef __RENDERER_HELPERS_XMLSCENE__
#define __RENDERER_HELPERS_XMLSCENE__

#include <iostream>
#include <memory>
#include <string>
#include "tinyxml2/tinyxml2.h"
#include "Renderer/Camera.h"
#include "Renderer/Light.h"
#include "Renderer/Model.h"
#include "Renderer/Scene.h"
#include "Renderer/SceneGraph.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/Helpers/CameraHelper.h"

namespace XMLHelper
{
  void importCamera( tinyxml2::XMLElement* el, Scene* scene );
  void importLight( tinyxml2::XMLElement* el, Scene* scene );
  void createSGNode( tinyxml2::XMLElement* el,
    std::shared_ptr<SceneGraph> scene_graph,
    std::shared_ptr<ResourceManager> resource_manager );
  Scene importScene( std::string file_name,
    std::shared_ptr<ResourceManager> resource_manager );
}

#endif