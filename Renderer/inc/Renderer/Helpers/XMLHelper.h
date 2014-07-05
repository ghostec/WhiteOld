#ifndef __RENDERER_HELPERS_XMLHELPER__
#define __RENDERER_HELPERS_XMLHELPER__

#include <iostream>
#include <memory>
#include <string>
#include "tinyxml2/tinyxml2.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"
#include "Renderer/Model.h"
#include "Renderer/Camera.h"
#include "Renderer/Scene.h"
#include "Renderer/Light.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/GUIELement.h"
#include "Renderer/GUIManager.h"
#include "Renderer/GUIScene.h"
#include "WMath/WMath.h"

namespace XMLHelper
{
  const char* parseString( tinyxml2::XMLElement* element, const char* name );
  WMath::vec3 parseVec3( tinyxml2::XMLElement* element, const char* name );

  std::shared_ptr<Camera> parseCamera( tinyxml2::XMLElement* element );
  std::shared_ptr<Shader> parseShader( tinyxml2::XMLElement* element );
  std::shared_ptr<Texture> parseTexture( tinyxml2::XMLElement* element );
  std::shared_ptr<Mesh> parseMesh( tinyxml2::XMLElement* element );

  Scene loadScene( std::string file_name,
    std::shared_ptr<ResourceManager> resource_manager );
  void loadAssets( std::string file_name,
    std::shared_ptr<ResourceManager> resource_manager );

  std::shared_ptr<GUIElement> parseGUIElement
    ( tinyxml2::XMLElement* element, GUIScene* gui_scene,
    std::shared_ptr<ResourceManager> resource_manager );

  GUIScene loadGUIScene( std::string file_name, GUIManager* gui_manager,
    std::shared_ptr<ResourceManager> resource_manager );
}

#endif