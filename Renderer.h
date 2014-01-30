#ifndef __WHITE_RENDERER__
#define __WHITE_RENDERER__

#include <iostream>
#include "GLFWhelper.h"
#include "Window.h"

class Renderer
{
  private:
    Window *window;
  public:
    Renderer();
    void render();
};

Renderer::Renderer()
{
  this->window = new Window();
}

#endif
