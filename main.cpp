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
  Renderer r;
  Input i;
  i.setWindow( &w );
  r.setWindow( &w );
  r.setInput( &i );
  r.render();
  return 0;
}
