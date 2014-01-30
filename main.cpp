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

  InputContext ic;
  ic.window = &w;
  Input i( ic );

  RendererContext rc;
  rc.window = &w;
  rc.input = &i;
  Renderer r( rc );

  r.render();
  return 0;
}
