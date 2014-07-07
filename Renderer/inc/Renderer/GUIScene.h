#ifndef __RENDERER_GUISCENE__
#define __RENDERER_GUISCENE__

#include <queue>
#include <map>
#include <memory>
#include "Renderer/Scene.h"
#include "Renderer/GUIElement.h"
#include "Input/Input.h"

// TODO: setDimensions of container

class GUIScene
{
  private:
    std::shared_ptr<GUIElement> container;
    Scene scene;
  public:
    GUIScene( std::shared_ptr<GUIElement> container );
    void update();
    // getters
    std::shared_ptr<GUIElement> getContainer() { return this->container; }
    Scene* getScene() { return &this->scene; }
};

#endif
