#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"

int main()
{
  Renderer r;
  r.render();
  std::cout << "Test" << std::endl;
  return 0;
}
