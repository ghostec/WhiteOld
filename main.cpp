#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLFWhelper.h"
#include "Renderer.h"
#include "Window.h"
#include "Input.h"

int main()
{
  Window w;
  // Input
  GLFWcontext glfwc;
  glfwc.window = &w;
  Input *i = new InputGLFW( glfwc );
  // Renderer
  RendererContext rc;
  rc.window = &w;
  rc.input = i;
  Renderer r( rc );
  // Start rendering
  r.render();
  return 0;
}
