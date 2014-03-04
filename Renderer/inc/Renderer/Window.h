#ifndef __WHITE_WINDOW__
#define __WHITE_WINDOW__

#include "Renderer/GLFWhelper.h"

#define WindowVar GLFWwindow

class Window
{
  private:
    WindowVar *windowvar;
  public:
    Window();
    WindowVar *getWindow();
};

#endif
