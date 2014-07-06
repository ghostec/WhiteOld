#ifndef __RENDERER_GUISCENE__
#define __RENDERER_GUISCENE__

#include <queue>
#include <map>
#include <memory>
#include "Renderer/Scene.h"
#include "Renderer/GUIElement.h"
#include "Input/Input.h"

class GUIScene
{
  private:
    std::shared_ptr<GUIElement> window;
    Scene scene;
  public:
    GUIScene( std::shared_ptr<GUIElement> window );
    void update();
    // getters
    Scene* getScene() { return &this->scene; }
};

#endif
