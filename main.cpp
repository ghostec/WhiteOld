#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "White.h"
#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Renderer.h"
#include "Renderer/Window.h"
#include "Renderer/Shader.h"
#include "Renderer/ModelAsset.h"
#include "Renderer/ModelInstance.h"
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

  Shader shader_standard( "standard" );

  ModelAsset model_asset( "../assets/models/cube.obj" );

  model_asset.addShader( &shader_standard );

  ModelInstance model_instance( &model_asset );
  ModelInstance model_instance2( &model_asset );

  Camera camera(  WMath::vec3(-2.0f, 3.0f, 8.0f),
                  WMath::vec3(0.0f, 0.0f, 0.0f) );

  Light light(  WMath::vec3( 0.0f, 0.0f, -100.0f ),
                WMath::vec3( 1.0f, 1.0f, 1.0f ), 0.2f, 0.005f );

  input->registerObserver(  "ARROW_UP_PRESS", 
                            std::bind(  [&]() { model_instance.moves.ARROW_UP = true; } ), 
                            "model" );
  input->registerObserver(  "ARROW_UP_RELEASE",
                            std::bind( [&] ( ) { model_instance.moves.ARROW_UP = false; } ),
                            "model" );

  input->registerObserver(  "ARROW_DOWN_PRESS",
                            std::bind( [&] ( ) { model_instance.moves.ARROW_DOWN = true; } ),
                            "model" );
  input->registerObserver(  "ARROW_DOWN_RELEASE",
                            std::bind( [&] ( ) { model_instance.moves.ARROW_DOWN = false; } ),
                            "model" );

  Scene scene;
  scene.addModel( &model_instance );
  scene.addModel( &model_instance2 );
  scene.addLight( &light );
  scene.setCamera( &camera );

  input->registerObserver(  "CLICK",
                            std::bind( &Scene::mousePicking, &scene ),
                            "scene" );

  light.setPosition( WMath::vec3( -3.0f, 0.0f, 2.0f ) );

  WMath::translate( model_instance2.getTransform( ), WMath::vec3( 0.0f, 3.0f, 0.0f ) );

  //WMath::rotate_y( &model1.model_data.transformation, 90.0f );
  //WMath::scale( &model1.model_data.transformation, 
  //              WMath::vec3( 2.0f, 2.0f, 2.0f ) );

  Renderer* renderer = white.getRenderer();
  renderer->setCurrentScene( &scene );
  renderer->render();

  return 0;
}
