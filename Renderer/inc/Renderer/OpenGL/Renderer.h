#ifndef __RENDERER_OPENGLRENDERER__
#define __RENDERER_OPENGLRENDERER__

#include <iostream>
#include <queue>
#include <vector>
#include "Renderer/Helpers/RendererHelper.h"
#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Window.h"
#include "Renderer/Mesh.h"
#include "Renderer/Model.h"
#include "Renderer/Scene.h"
#include "Renderer/SceneGraph.h"
#include "Renderer/SceneEditor.h"
#include "Renderer/Viewport.h"
#include "Input/Input.h"

class Renderer
{
  private:
    Window* window;
    std::shared_ptr<Viewport> viewport;
    // methods
    void drawScene( Scene* scene );
  public:
    Renderer( Window* window );
    void render();
    void setViewport( std::shared_ptr<Viewport> viewport );
};

#endif
