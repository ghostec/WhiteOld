#ifndef __RENDERER_GUISCENE__
#define __RENDERER_GUISCENE__

#include <vector>
#include <memory>
#include "Renderer/Scene.h"
#include "Renderer/GUIElement.h"
#include "Input/Input.h"

class GUIScene
{
  private:
    std::vector< std::shared_ptr<GUIElement> > gui_elements;
    Scene scene;
  public:
    void addGUIElement( std::shared_ptr<GUIElement> gui_element );
    void update();
    // getters
    Scene* getScene() { return &this->scene; }
};

#endif
