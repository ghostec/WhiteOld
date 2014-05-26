#ifndef __RENDERER_GUISCENE__
#define __RENDERER_GUISCENE__

#include <vector>
#include "Renderer/Scene.h"
#include "Renderer/GUIInstance.h"
#include "Renderer/MousePicking.h"
#include "Input/Input.h"

class GUIScene
{
  private:
    Scene* scene;
    std::vector< GUIInstance* > gui_instances;
    MousePicking mouse_picking;
  public:
    GUIScene( Scene* scene );
    void addGUIInstance( GUIInstance* gui_instance );
    void pollEvents();
};

#endif
