#ifndef __WHITE_RENDERER__
#define __WHITE_RENDERER__

#include <iostream>
#include "GLFWhelper.h"
#include "Window.h"
#include "Input.h"
#include "Model.h"

typedef struct _RendererContext
{
  Window *window;
  Input *input;
} RendererContext;

class Renderer
{
  private:
    RendererContext context;
    Model* model;
    void setWindow( Window* window );
    void setInput( Input* input );
  public:
    Renderer( RendererContext rc );
    void render();
    void setModel( Model* model );
};

Renderer::Renderer( RendererContext rc )
{
  this->setWindow( rc.window );
  this->setInput( rc.input );
}

void Renderer::setWindow( Window *window )
{
  this->context.window = window;
}

void Renderer::setInput( Input *input )
{
  this->context.input = input;
}

void Renderer::render()
{
  while ( not glfwWindowShouldClose( this->context.window->getWindow() ) &&
          not context.input->isKeyPressed( GLFW_KEY_ESCAPE ) )
  {
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw a rectangle from the 2 triangles using 6 indices
    this->model->draw();

    glfwSwapBuffers( this->context.window->getWindow() );
    glfwPollEvents();
  }
}

void Renderer::setModel( Model* model )
{
  this->model = model;
}

#endif
