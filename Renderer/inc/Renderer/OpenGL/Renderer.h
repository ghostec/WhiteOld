#ifndef __RENDERER_OPENGLRENDERER__
#define __RENDERER_OPENGLRENDERER__

#include <iostream>
#include <memory>
#include "Renderer/Helpers/RendererHelper.h"
#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Window.h"
#include "Renderer/Mesh.h"
#include "Renderer/Model.h"
#include "Renderer/Scene.h"
#include "Renderer/SceneGraph.h"
#include "Renderer/SceneEditor.h"
#include "WMath/WMath.h"
#include "Input/Input.h"

class Renderer
{
  private:
    Window* window;
    std::vector< Scene* > scenes;
    void drawScene( Scene* scene );
  public:
    Renderer( Window* window );
    void render();
    void addScene( Scene* scene );
    void setScenes( std::vector<Scene*> scenes );
};

#endif
