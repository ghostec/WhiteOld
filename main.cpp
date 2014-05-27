#define GLEW_STATIC
#include <iostream>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Renderer.h"
#include "Renderer/Window.h"
#include "Renderer/Shader.h"
#include "Renderer/ModelAsset.h"
#include "Renderer/ModelInstance.h"
#include "Renderer/Camera.h"
#include "Renderer/Scene.h"
#include "Renderer/Light.h"
#include "Renderer/MousePicking.h"
#include "Renderer/SceneEditor.h"
#include "Renderer/GUIAsset.h"
#include "Renderer/GUIInstance.h"
#include "Renderer/GUIScene.h"
#include "Renderer/Effect.h"
#include "Input/Input.h"

int main()
{
  Window window;
  
  Input input( window.getWindow() );
  active_input = &input;

  Camera camera(  WMath::vec3(-2.0f, 3.0f, 8.0f),
                  WMath::vec3(0.0f, 0.0f, 0.0f) );

  Light light(  WMath::vec3( 0.0f, 0.0f, -100.0f ),
                WMath::vec3( 1.0f, 1.0f, 1.0f ), 0.2f, 0.005f );

  Scene scene;
  scene.addLight( &light );
  scene.setCamera( &camera );

  GUIAsset gui_asset( 100.0f, 100.0f );
  GUIInstance gui_instance( &gui_asset, 0.05f, 4.0f/3.0f );
  GUIInstance gui_instance2( &gui_asset, 0.05f, 4.0f / 3.0f );
  GUIScene gui_scene( &scene );
  gui_scene.addGUIInstance( &gui_instance );
  gui_scene.addGUIInstance( &gui_instance2 );

  gui_instance2.translate( 0.0f, 62.0f );

  light.setPosition( WMath::vec3( -3.0f, 0.0f, 2.0f ) );
  Renderer renderer( &window, nullptr );
  renderer.setCurrentScene( &scene );

  auto t0 = std::chrono::high_resolution_clock::now();

  EffectComponent effect_component2;
  effect_component2.initial_value = 0.0f;
  effect_component2.final_value = 0.1f;
  effect_component2.duration = 5.0f;
  effect_component2.interpolation_function = &interpolation_function;
  effect_component2.effect_function = &effect_function2;
  Effect effect( gui_instance.getModelInstance() );
  effect.addComponent( fadeOut( 1.0f ) );
  effect.addComponent( effect_component2 );

  while(  window.isOpen() &&
          !active_input->isKeyPressed( GLFW_KEY_ESCAPE ) )
  {
    gui_scene.pollEvents();
    renderer.render();
    effect.execute();
    while( std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::high_resolution_clock::now() - t0 ).count() < 16.6666666667 );
    t0 = std::chrono::high_resolution_clock::now();
  }

  return 0;
}
