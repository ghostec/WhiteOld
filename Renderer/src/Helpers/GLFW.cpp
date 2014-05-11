#include "Renderer/Helpers/GLFW.h"

namespace GLFWhelper
{
  GLFWwindow* CreateWindow()
  {
    if( ! glfwInit() )
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
    glfwSetKeyCallback( window, keyboardCallback );

    glewExperimental = GL_TRUE;
    glewInit();

    // OpenGL
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    return window;
  }

  bool isKeyPressed( GLFWwindow *window, int key )
  {
    if( glfwGetKey( window, key ) == GLFW_PRESS )
      return true;
    else
      return false;
  }
}
