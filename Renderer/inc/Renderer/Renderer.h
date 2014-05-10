#ifndef __WHITE_RENDERER__
#define __WHITE_RENDERER__

#include <iostream>
#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Window.h"
#include "Renderer/Model.h"
#include "Renderer/Scene.h"
#include "Input/Input.h"

typedef struct _RendererContext
{
  Window *window;
  Input *input;
} RendererContext;

class Renderer
{
  private:
    RendererContext context;
    Scene* current_scene;
    void setWindow( Window* window );
    void setInput( Input* input );
  public:
    Renderer( RendererContext rc );
    void render();
    void setCurrentScene( Scene* scene );
};

#endif
