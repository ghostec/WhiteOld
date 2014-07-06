#ifndef __RENDERER_GUIMANAGER__
#define __RENDERER_GUIMANAGER__

#include <string>
#include "Renderer/Mesh.h"
#include "Renderer/Model.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/GUIElement.h"
#include "Renderer/ResourceManager.h"
#include "WMath/WMath.h"

class GUIManager
{
  private:
    std::shared_ptr<ResourceManager> resource_manager;
    std::map< std::string, std::shared_ptr<GUIElement> > gui_element;
    std::shared_ptr<Mesh> square_mesh;
  public:
    GUIManager( std::shared_ptr<ResourceManager> resource_manager  );
    void createGUIElement
      ( std::string name, WMath::vec2 dimensions, WMath::vec2 offset = { 0, 0 },
      WMath::vec2 offset_percent = { 0, 0 }, GUIType gui_type = CONTAINER );
    void createGUIElement
      ( std::string name, std::string parent, float parent_percent = 1,
      WMath::vec2 offset = { 0, 0 }, WMath::vec2 offset_percent = { 0, 0 },
      GUIType = DRAWNABLE );
    // getters
    std::shared_ptr<GUIElement> getGUIElement( std::string name )
      { return this->gui_element[name]; }
};

#endif