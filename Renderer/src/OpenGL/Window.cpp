#include "Renderer/OpenGL/Window.h"

Window* active_window;

Window::Window( WMath::vec2 dimensions )
{
  this->window = GLFWhelper::CreateWindow( dimensions );
  this->dimensions = dimensions;
  this->dirty = true;
}

void Window::setDimensions( WMath::vec2 d )
{
  this->dimensions = d;
  this->notify( "RESIZE" );
  this->dirty = true;
}

bool Window::isOpen()
{
  return !glfwWindowShouldClose( this->window );
}