#ifndef __WHITE_OPENGLRENDERER__
#define __WHITE_OPENGLRENDERER__

#include <iostream>
#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Window.h"
#include "Renderer/Model.h"
#include "Renderer/Scene.h"
#include "Input/Input.h"

typedef struct _RendererContext
{
  Window *window;
} RendererContext;

class Renderer
{
  private:
    RendererContext context;
    Scene* current_scene;
    void setWindow( Window* window );
  public:
    Renderer( RendererContext rc );
    void render();
    void setCurrentScene( Scene* scene );
};

#endif
