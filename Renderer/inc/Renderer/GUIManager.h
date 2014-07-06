#ifndef __RENDERER_GUIMANAGER__
#define __RENDERER_GUIMANAGER__

#include <string>
#include "Renderer/Mesh.h"
#include "Renderer/Model.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/GUIScene.h"
#include "Renderer/GUIElement.h"
#include "Renderer/ResourceManager.h"
#include "WMath/WMath.h"

class GUIManager
{
  private:
    std::shared_ptr<ResourceManager> resource_manager;
    std::map< std::string, std::shared_ptr<GUIElement> > gui_element;
    std::map< std::string, std::shared_ptr<GUIScene> > gui_scene;
    std::shared_ptr<Mesh> square_mesh;
  public:
    GUIManager( std::shared_ptr<ResourceManager> resource_manager  );
    void createGUIScene( std::string name );
    void createGUIElement( std::string name, std::string scene_name,
      std::string parent_name = "", GUIType gui_type = DRAWNABLE );
    // getters
    std::shared_ptr<GUIScene> getGUIScene( std::string name )
    { return this->gui_scene[name]; }
    std::shared_ptr<GUIElement> getGUIElement( std::string name )
      { return this->gui_element[name]; }
};

#endif