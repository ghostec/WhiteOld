#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLFWhelper.h"
#include "White.h"
#include "Renderer.h"
#include "Window.h"
#include "Input.h"
#include "ModelFactory.h"
#include "Model.h"
#include "Scene.h"
#include "Mesh.h"

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
