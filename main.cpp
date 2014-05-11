#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "White.h"
#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Renderer.h"
#include "Renderer/Window.h"
#include "Renderer/Model.h"
#include "Renderer/Camera.h"
#include "Renderer/Scene.h"

void bar()
{
  std::cout << "bartender" << std::endl;
}

int main()
{
  White white;
  white.setArchitecture( OSX );
  
  Input* input = white.getInput();
  input->registerObserver( "test", std::bind(bar) );
  input->notify( "test" );

  Model model1( "../assets/models/cow.obj" );

  Camera camera( WMath::vec3(0.0f, 3.0f, 2.0f),
                  WMath::vec3(0.0f, 0.0f, 0.0f) );

  Scene scene;
  scene.addModel( &model1 );
  scene.setCamera( &camera );

  model1.rotate( 30.0f );
  model1.scale( WMath::vec3( 1.5f, 1.5f, 1.5f ) );
  model1.translate( WMath::vec3( 0.0f, 0.0f, 0.0f ) );

  Renderer* renderer = white.getRenderer();
  renderer->setCurrentScene( &scene );
  renderer->render();

  return 0;
}
