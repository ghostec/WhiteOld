#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "White.h"
#include "Renderer/GLFWhelper.h"
#include "Renderer/Renderer.h"
#include "Renderer/Window.h"
#include "Renderer/ModelFactory.h"
#include "Renderer/Model.h"
#include "Renderer/Scene.h"

int main()
{
  White white;
  white.setArchitecture( OSX );

  ModelFactory *model_factory = white.getModelFactory();
  Model *model = model_factory->createModel( OBJ, "file_path" );

  Scene scene;
  scene.addModel( model );

  Renderer *renderer = white.getRenderer();
  renderer->setCurrentScene( &scene );
  renderer->render();

  return 0;
}
