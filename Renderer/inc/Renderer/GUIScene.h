#ifndef __WHITE_RENDERER_GUISCENE__
#define __WHITE_RENDERER_GUISCENE__

#include "Renderer/Viewport.h"
#include "Renderer/GUIElement.h"
#include "Renderer/Containable.h"

class GUIScene
{
  private:
    std::shared_ptr<Viewport> viewport;
    std::shared_ptr<GUIElement> rootGUIElement;
  public:
    GUIScene() {};
    void update();
    void setViewport( std::shared_ptr<Viewport> v ) { this->viewport = v; }
    void setRootGUIElement( std::shared_ptr<GUIElement> g )
      { this->rootGUIElement = g; }
    std::shared_ptr<Viewport> getViewport() { return viewport; }
    std::shared_ptr<GUIElement> getRootGUIElement() { return rootGUIElement; }
};

#endif
