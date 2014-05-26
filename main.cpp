#define GLEW_STATIC
#include <iostream>
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
  GUIInstance gui_instance( &gui_asset, 0.1f, 4.0f/3.0f );
  GUIInstance gui_instance2( &gui_asset, 0.1f, 4.0f / 3.0f );

  scene.addModel( gui_instance.getModelInstance() );
  scene.addModel( gui_instance2.getModelInstance( ) );
  gui_instance2.translate( 0.0f, 62.0f );

  light.setPosition( WMath::vec3( -3.0f, 0.0f, 2.0f ) );
  Renderer renderer( &window, nullptr );
  renderer.setCurrentScene( &scene );

  while(  window.isOpen() &&
          !active_input->isKeyPressed( GLFW_KEY_ESCAPE ) )
  {
    renderer.render();
  }

  return 0;
}
