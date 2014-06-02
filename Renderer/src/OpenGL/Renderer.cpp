#include "Renderer/OpenGL/Renderer.h"

Renderer::Renderer( Window* window )
{
  this->window = window;
}

void Renderer::render()
{
    // Clear the screen to black
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for( Scene* scene : this->scenes )
    {
      scene->draw();
    }

    glfwSwapBuffers( this->window->getWindow() );
    glfwPollEvents();
}

void Renderer::addScene( Scene* scene )
{
  this->scenes.push_back( scene );
}
