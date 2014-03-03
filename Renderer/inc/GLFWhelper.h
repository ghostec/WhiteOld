#ifndef __WHITE_GLFWHELPER__
#define __WHITE_GLFWHELPER__

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace GLFWhelper
{
  GLFWwindow* CreateWindow();
  bool isKeyPressed( GLFWwindow *window, int key );
}

#endif
