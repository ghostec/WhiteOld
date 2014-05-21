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
#include "Renderer/Light.h"
#include "Input/Input.h"

int main()
{
  White white;
  white.setArchitecture( OSX );
  
  Input* input = white.getInput();
  active_input = input;

  Model model( "../assets/models/cube.obj" );

  Camera camera(  WMath::vec3(2.0f, 3.0f, -10.0f),
                  WMath::vec3(0.0f, 0.0f, 0.0f) );

  Light light(  WMath::vec3( 0.0f, 0.0f, -100.0f ),
                WMath::vec3( 1.0f, 1.0f, 1.0f ), 0.2f, 0.005f );

  input->registerObserver(  "ARROW_UP_PRESS", 
                            std::bind(  [&]() { model.moves.ARROW_UP = true; } ), 
                            "model1" );
  input->registerObserver(  "ARROW_UP_RELEASE",
                            std::bind(  [&] () { model.moves.ARROW_UP = false; } ),
                            "model1" );

  input->registerObserver(  "ARROW_DOWN_PRESS",
                            std::bind( [&] () { model.moves.ARROW_DOWN = true; } ),
                            "model1" );
  input->registerObserver(  "ARROW_DOWN_RELEASE",
                            std::bind( [&] () { model.moves.ARROW_DOWN = false; } ),
                            "model1" );

  Scene scene;
  scene.addModel( &model );
  scene.addLight( &light );
  scene.setCamera( &camera );

  light.setPosition( WMath::vec3( 0.0f, 0.0f, -2.0f ) );

  //WMath::rotate_y( &model1.model_data.transformation, 90.0f );
  //WMath::scale( &model1.model_data.transformation, 
  //              WMath::vec3( 2.0f, 2.0f, 2.0f ) );

  Renderer* renderer = white.getRenderer();
  renderer->setCurrentScene( &scene );
  renderer->render();

  return 0;
}
