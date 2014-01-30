#include "Renderer.h"

void Renderer::render()
{
  while(!glfwWindowShouldClose(this->window))
  {
    glfwSwapBuffers(this->window);
    glfwPollEvents();
  }
}
