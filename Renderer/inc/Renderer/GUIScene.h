#ifndef __RENDERER_GUISCENE__
#define __RENDERER_GUISCENE__

#include <map>
#include <memory>
#include "Renderer/Scene.h"
#include "Renderer/GUIElement.h"
#include "Input/Input.h"

class GUIScene
{
  private:
    std::map< std::string, std::shared_ptr<GUIElement> > gui_elements;
    Scene scene;
  public:
    void addGUIElement( std::string name,
      std::shared_ptr<GUIElement> gui_element );
    void update();
    // getters
    Scene* getScene() { return &this->scene; }
    std::shared_ptr<GUIElement> getGUIElement( std::string name )
      { return this->gui_elements[name]; }
};

#endif
