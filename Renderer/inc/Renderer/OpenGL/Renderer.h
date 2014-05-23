#ifndef __RENDERER_OPENGLRENDERER__
#define __RENDERER_OPENGLRENDERER__

#include <iostream>
#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Window.h"
#include "Renderer/ModelAsset.h"
#include "Renderer/Scene.h"
#include "Renderer/SceneEditor.h"
#include "Input/Input.h"

class Renderer
{
  private:
    Window* window;
    Scene* current_scene;
    SceneEditor* scene_editor;
  public:
    Renderer( Window* window, SceneEditor* scene_editor );
    void render();
    void setCurrentScene( Scene* scene );
};

#endif
