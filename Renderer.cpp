#include "Renderer.h"

Renderer::Renderer()
{
  if( !glfwInit() )
    std::cout << "could not initialize GLFW" << std::endl;

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "Window Name", NULL, NULL);
  if ( !window )
  {
    glfwTerminate();
    std::cout << "could not create glfw window" << std::endl;
  }

  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  glewInit();

  this->window = window;
}

void Renderer::render()
{
  while(!glfwWindowShouldClose(this->window))
  {
    glfwSwapBuffers(this->window);
    glfwPollEvents();
  }
}
