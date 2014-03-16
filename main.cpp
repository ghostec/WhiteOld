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
#include "Renderer/CameraFactory.h"
#include "Renderer/Scene.h"

int main()
{
  White white;
  white.setArchitecture( OSX );

  ModelFactory* model_factory = white.getModelFactory();
  Model* model1 = model_factory->createModel( OBJ, "file_path" );

  CameraFactory* camera_factory = white.getCameraFactory();
  Camera* camera = camera_factory->createCamera(
                                  WMath::vec3(0.0f, 3.0f, 2.0f),
                                  WMath::vec3(0.0f, 0.0f, 0.0f) );

  Scene scene;
  scene.addModel( model1 );

  model1->rotate( 30.0f );
  model1->scale( WMath::vec3( 0.5f, 0.5f, 0.5f ) );
  model1->translate( WMath::vec3( 0.0f, 0.0f, 0.0f ) );

  Renderer* renderer = white.getRenderer();
  renderer->setCurrentScene( &scene );
  renderer->render();

  return 0;
}
