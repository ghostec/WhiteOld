#ifndef __RENDERER_GUISCENE__
#define __RENDERER_GUISCENE__

#include <queue>
#include <map>
#include <memory>
#include <string>
#include "Renderer/Scene.h"
#include "Renderer/GUIElement.h"
#include "Input/Input.h"

// TODO: setDimensions of container

class GUIScene
{
  private:
    std::shared_ptr<GUIElement> container;
    std::shared_ptr<Scene> scene;
  public:
    GUIScene( std::shared_ptr<GUIElement> container, std::string name );
    void update();
    // getters
    std::shared_ptr<GUIElement> getContainer() { return this->container; }
    Scene* getScene() { return &*this->scene; }
};

#endif
