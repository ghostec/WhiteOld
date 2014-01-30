#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLFWhelper.h"
#include "White.h"
#include "Renderer.h"
#include "Window.h"
#include "Input.h"

int main()
{
  White white;
  white.setArchitecture( OSX );
  // Start rendering
  white.getRenderer()->render();
  //r.render();
  return 0;
}
