#define GLEW_STATIC
#include <iostream>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Renderer.h"
#include "Renderer/Window.h"
#include "Renderer/Scene.h"
#include "Renderer/GUIManager.h"
#include "Renderer/GUIElement.h"
#include "Renderer/GUIScene.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/Helpers/XMLAssets.h"
#include "Renderer/Helpers/XMLScene.h"
#include "Renderer/Helpers/XMLGUIScene.h"
#include "Renderer/Helpers/CameraHelper.h"
#include "Renderer/MousePicking.h"
#include "Renderer/SceneGraph.h"
#include "Renderer/SGNode.h"
#include "Input/Input.h"
#include "Physics/PhysicsManager.h"
#include "Physics/Helpers/XMLPhysics.h"

int main()
{
  Window window( WMath::vec2( 800, 600 ) );
  active_window = &window;

  Input input( window.getWindow() );
  active_input = &input;

  std::shared_ptr<ResourceManager> resource_manager( new ResourceManager );

  XMLHelper::importAssets( "assets", resource_manager );
  std::shared_ptr<Scene> scene =
    std::make_shared<Scene>
    ( XMLHelper::importScene( "example", resource_manager ) );
  Camera* camera = &*scene->getCamera();
  CameraHelper::normalCamera( camera );
  WMath::translate( camera->getView(), WMath::vec3( -1, -4, -13 ) );

  Renderer renderer( &window );
  renderer.addScene( &*scene );

  SceneEditor scene_editor( scene, resource_manager );
  scene_editor.initialize();

  std::shared_ptr<PhysicsManager> physics_manager( new PhysicsManager );
  XMLHelper::importPhysics( "physics_example", scene->getSceneGraph(), physics_manager );

  auto t0 = std::chrono::high_resolution_clock::now();

  while(  window.isOpen() &&
          !active_input->isKeyPressed( GLFW_KEY_ESCAPE ) )
  {
    physics_manager->update();
    scene_editor.update();
    renderer.render();
    while( std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::high_resolution_clock::now() - t0 ).count() < 16.6666666667 );
    t0 = std::chrono::high_resolution_clock::now();
  }

  return 0;
}
