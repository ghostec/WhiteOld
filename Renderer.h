#ifndef __WHITE_RENDERER__
#define __WHITE_RENDERER__

#include <iostream>
#include "GLFWhelper.h"
#include "Window.h"
#include "Input.h"

class Renderer
{
  private:
    Window *window;
    Input *input;
  public:
    void setWindow( Window *window );
    void setInput( Input *input );
    void render();
};

void Renderer::setWindow( Window *window )
{
  this->window = window;
}

void Renderer::setInput( Input *input )
{
  this->input = input;
}

void Renderer::render()
{
  while ( not glfwWindowShouldClose( this->window->getWindow() ) &&
          not input->isKeyPressed( GLFW_KEY_ESCAPE ) )
  {
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw a rectangle from the 2 triangles using 6 indices

    glfwSwapBuffers( this->window->getWindow() );
    glfwPollEvents();
  }
}

#endif
