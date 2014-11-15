#ifndef __WHITE_RENDERER_GUISCENE__
#define __WHITE_RENDERER_GUISCENE__

#include <string>
#include "Renderer/Viewport.h"
#include "Renderer/GUIElement.h"
#include "Renderer/Containable.h"

class GUIScene
{
  private:
    std::string name;
    std::shared_ptr<Viewport> viewport;
    std::shared_ptr<GUIElement> rootGUIElement;
    std::shared_ptr<SceneGraph> scene_graph;
    std::shared_ptr<Scene> scene;
  public:
    GUIScene( std::string name );
    void update();
    void setViewport( std::shared_ptr<Viewport> v ) { this->viewport = v; }
    void setRootGUIElement( std::shared_ptr<GUIElement> g );
    std::shared_ptr<Viewport> getViewport() { return viewport; }
    std::shared_ptr<GUIElement> getRootGUIElement() { return rootGUIElement; }
    std::shared_ptr<Scene> getScene() { return this->scene; }
};

#endif
