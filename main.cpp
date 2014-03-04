#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/inc/GLFWhelper.h"
#include "White.h"
#include "Renderer/inc/Renderer.h"
#include "Renderer/inc/Window.h"
#include "Renderer/inc/ModelFactory.h"
#include "Renderer/inc/Model.h"
#include "Renderer/inc/Scene.h"
#include "Renderer/inc/Mesh.h"

int main()
{
  White white;
  white.setArchitecture( OSX );

  ModelFactory *model_factory = white.getModelFactory();
  Model *model = model_factory->createModel( OBJ, "file_path" );
  Mesh mesh( model );

  Scene scene;
  scene.addMesh( &mesh );

  Renderer *renderer = white.getRenderer();
  renderer->setCurrentScene( &scene );
  renderer->render();

  return 0;
}
