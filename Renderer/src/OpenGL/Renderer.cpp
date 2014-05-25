#include "Renderer/OpenGL/Renderer.h"

Renderer::Renderer( Window* window, SceneEditor* scene_editor )
{
  this->window = window;
  this->scene_editor = scene_editor;
}

void Renderer::render()
{
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->current_scene->draw();

    glfwSwapBuffers( this->window->getWindow() );
    glfwPollEvents();
}

void Renderer::setCurrentScene( Scene* scene )
{
  this->current_scene = scene;
}
