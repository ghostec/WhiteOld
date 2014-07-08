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
#include "Renderer/ResourceManager.h"

namespace XMLHelper
{
  void importCamera( tinyxml2::XMLElement* el, Scene* scene );
  void importLight( tinyxml2::XMLElement* el, Scene* scene );
  void importModel( tinyxml2::XMLElement* el, Scene* scene,
    std::shared_ptr<ResourceManager> resource_manager );
  Scene importScene( std::string file_name,
    std::shared_ptr<ResourceManager> resource_manager );
}

#endif