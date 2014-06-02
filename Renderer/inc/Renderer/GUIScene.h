#ifndef __RENDERER_GUISCENE__
#define __RENDERER_GUISCENE__

#include <vector>
#include <memory>
#include "Renderer/Scene.h"
#include "Renderer/GUIInstance.h"
#include "Renderer/MousePicking.h"
#include "Input/Input.h"

class GUIScene
{
  private:
    std::shared_ptr<Scene> scene;
    std::vector< std::shared_ptr<GUIInstance> > gui_instances;
    MousePicking mouse_picking;
  public:
    GUIScene( std::shared_ptr<Scene> scene );
    void addGUIInstance( std::shared_ptr<GUIInstance> gui_instance );
    void pollEvents();
};

#endif
