#include <Window.h>

Window::Window()
{
  this->windowvar = GLFWhelper::CreateWindow();
}

WindowVar* Window::getWindow()
{
  return this->windowvar;
}
