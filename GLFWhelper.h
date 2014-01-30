#ifndef __WHITE_GLFWHELPER__
#define __WHITE_GLFWHELPER__

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace GLFWhelper
{
  GLFWwindow* CreateWindow()
  {
    if( not glfwInit() )
      std::cout << "couldn't initialize GLFW" << std::endl;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Simple example", NULL, NULL);
    if ( !window )
    {
      glfwTerminate();
      std::cout << "couldn't create GLFW window" << std::endl;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    return window;
  }
}

#endif
