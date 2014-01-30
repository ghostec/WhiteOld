#ifndef __WHITE_WINDOW__
#define __WHITE_WINDOW__

#include "GLFWhelper.h"

#define WindowVar GLFWwindow

class Window
{
  private:
    WindowVar *windowvar;
  public:
    Window();
    WindowVar *getWindow();
};

Window::Window()
{
  this->windowvar = GLFWhelper::CreateWindow();
}

WindowVar* Window::getWindow()
{
  return this->windowvar;
}

#endif
