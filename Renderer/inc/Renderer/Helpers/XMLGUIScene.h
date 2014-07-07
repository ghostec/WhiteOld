#ifndef __RENDERER_HELPERS_XMLGUISCENE__
#define __RENDERER_HELPERS_XMLGUISCENE__

#include <iostream>
#include <memory>
#include <string>
#include "tinyxml2/tinyxml2.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/GUIELement.h"
#include "Renderer/GUIManager.h"
#include "Renderer/GUIScene.h"

namespace XMLHelper
{
  void importGUIElement( tinyxml2::XMLElement* el, GUIManager* gui_manager,
    std::string gui_scene_name );
  void importGUIScene( std::string file_name, GUIManager* gui_manager );
}

#endif