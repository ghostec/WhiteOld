#include "Renderer/Window.h"

Window::Window()
{
  this->window = GLFWhelper::CreateWindow();
}

bool Window::isOpen()
{
  return !glfwWindowShouldClose( this->window );
}

GLFWwindow* Window::getWindow( )
{
  return this->window;
}
