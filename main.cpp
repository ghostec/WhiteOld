#define GLEW_STATIC
#include <iostream>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Renderer.h"
#include "Renderer/Window.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"
#include "Renderer/Model.h"
#include "Renderer/Camera.h"
#include "Renderer/Scene.h"
#include "Renderer/Light.h"
#include "Renderer/MousePicking.h"
#include "Renderer/SceneEditor.h"
#include "Renderer/GUIAsset.h"
#include "Renderer/GUIInstance.h"
#include "Renderer/GUIScene.h"
#include "Renderer/Effect.h"
#include "Renderer/EffectsManager.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/Helpers/XMLHelper.h"
#include "Input/Input.h"

int main()
{
  Window window;
  
  Input input( window.getWindow() );
  active_input = &input;

  std::shared_ptr<ResourceManager> resource_manager( new ResourceManager );
  std::shared_ptr<Scene> scene = XMLHelper::parseXMLScene( resource_manager );

  Light light( WMath::vec3( -3.0f, 0.0f, 2.0f ),
    WMath::vec3( 1.0f, 1.0f, 1.0f ), 0.2f, 0.005f );

  scene->addLight( std::shared_ptr<Light>( &light ) );
  light.setPosition( WMath::vec3( -3.0f, 0.0f, 2.0f ) );
  Renderer renderer( &window );
  renderer.addScene( scene.get() );

  auto t0 = std::chrono::high_resolution_clock::now();

  while(  window.isOpen() &&
          !active_input->isKeyPressed( GLFW_KEY_ESCAPE ) )
  {
    //gui_scene.pollEvents();
    renderer.render();
    while( std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::high_resolution_clock::now() - t0 ).count() < 16.6666666667 );
    t0 = std::chrono::high_resolution_clock::now();
  }

  return 0;
}
