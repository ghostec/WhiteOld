#include <Renderer.h>

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

    this->current_scene->draw();

    glfwSwapBuffers( this->context.window->getWindow() );
    glfwPollEvents();
  }
}

void Renderer::setCurrentScene( Scene* scene )
{
  this->current_scene = scene;
}