#ifndef __WHITE_GLFWHELPER__
#define __WHITE_GLFWHELPER__

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Input/Input.h>
#include "Renderer/Window.h"
#include "WMath/WMath.h"

namespace GLFWhelper
{
  GLFWwindow* CreateWindow( WMath::vec2 dimensions );
  bool isKeyPressed( GLFWwindow *window, int key );
  void windowResizeCallback( GLFWwindow *window, int w, int h );
}

#endif
