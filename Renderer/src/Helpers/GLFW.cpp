#include "Renderer/Helpers/GLFW.h"

namespace GLFWhelper
{
  GLFWwindow* CreateWindow( WMath::vec2 dimensions )
  {
    if( ! glfwInit() )
      std::cout << "couldn't initialize GLFW" << std::endl;

    glfwWindowHint(GLFW_SAMPLES, 32);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // set GLFW_DECORATED to GL_FALSE to have a borderless window
    glfwWindowHint( GLFW_DECORATED, GL_TRUE );

    GLFWwindow *window = glfwCreateWindow
      ( dimensions[0], dimensions[1], "White", NULL, NULL );

    if ( !window )
    {
      glfwTerminate();
      std::cout << "couldn't create GLFW window" << std::endl;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback( window, keyboardCallback );
    glfwSetMouseButtonCallback( window, mouseButtonCallback );
    glfwSetScrollCallback( window, mouseScrollCallback );
    glfwSetWindowSizeCallback( window, windowResizeCallback );

    glewExperimental = GL_TRUE;
    glewInit();

    // OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
    
    //glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );

    return window;
  }

  bool isintPressed( GLFWwindow *window, int Key )
  {
    if( glfwGetKey( window, Key ) == GLFW_PRESS )
      return true;
    else
      return false;
  }

  void windowResizeCallback( GLFWwindow *window, int w, int h )
  {
    active_window->setDimensions( WMath::vec2( w, h ) );
    active_window->setDirty( true );
  }
}
