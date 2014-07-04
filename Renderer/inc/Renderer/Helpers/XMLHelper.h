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
#include "WMath/WMath.h"

namespace XMLHelper
{
  const char* parseXMLstring( tinyxml2::XMLElement* element, const char* name );
  WMath::vec3 parseXMLvec3( tinyxml2::XMLElement* element, const char* name );
  std::shared_ptr<Camera> parseXMLCamera( tinyxml2::XMLElement* element );
  std::shared_ptr<Shader> parseXMLShader( tinyxml2::XMLElement* element );
  std::shared_ptr<Texture> parseXMLTexture( tinyxml2::XMLElement* element );
  std::shared_ptr<Mesh> parseXMLMesh( tinyxml2::XMLElement* element );
  std::shared_ptr<Scene> parseXMLScene
    ( std::shared_ptr<ResourceManager> resource_manager );
}

#endif