#ifndef __RENDERER_WINDOW__
#define __RENDERER_WINDOW__

#include "Renderer/Helpers/GLFW.h"

class Window
{
  private:
    GLFWwindow *window;
  public:
    Window();
    bool isOpen();
    GLFWwindow *getWindow( );
};

#endif
