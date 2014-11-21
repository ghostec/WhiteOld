#ifndef __RENDERER_HELPERS_XMLASSETS__
#define __RENDERER_HELPERS_XMLASSETS__

#include <iostream>
#include <memory>
#include <string>
#include "tinyxml2.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"
#include "Renderer/Texture.h"
#include "Renderer/Model.h"
#include "Renderer/ResourceManager.h"

namespace XMLHelper
{
  void importShader( tinyxml2::XMLElement* el,
    std::shared_ptr<ResourceManager> resource_manager );
  void importTexture( tinyxml2::XMLElement* el,
    std::shared_ptr<ResourceManager> resource_manager );
  void importMaterial( tinyxml2::XMLElement* el,
    std::shared_ptr<ResourceManager> resource_manager );
  void importMesh( tinyxml2::XMLElement* el,
    std::shared_ptr<ResourceManager> resource_manager );
  void importModel( tinyxml2::XMLElement* el,
    std::shared_ptr<ResourceManager> resource_manager );
  void importAssets( std::string file_name,
    std::shared_ptr<ResourceManager> resource_manager );
}

#endif