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
#include "Renderer/Viewport.h"
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
  CameraHelper::normalCamera( camera, 1 );
  WMath::translate( camera->getView(), WMath::vec3( -1, -4, -13 ) );

  Renderer renderer( &window );

  ViewportData data_1;
  data_1.mode = VIEWPORT_MODE_COLUMN;
  data_1.mode_data.column.size = 300;
  data_1.dimensions_mode = VIEWPORT_DIMENSIONS_MODE_ABSOLUTE;
  data_1.anchor = WMath::vec2(0);
  data_1.anchor_corner = VIEWPORT_ANCHOR_CORNER_TOP_RIGHT;
  data_1.anchor_mode = VIEWPORT_ANCHOR_MODE_ABSOLUTE;
  data_1.background = WMath::vec3( 1.0 );
  std::shared_ptr<Viewport> viewport_1
    ( new Viewport( data_1 ) );

  ViewportData data_2;
  data_2.mode = VIEWPORT_MODE_COLUMN;
  data_2.mode_data.column.size = 1;
  data_2.dimensions_mode = VIEWPORT_DIMENSIONS_MODE_RELATIVE;
  data_2.anchor = WMath::vec2( 250, 0 );
  data_2.anchor_corner = VIEWPORT_ANCHOR_CORNER_TOP_RIGHT;
  data_2.anchor_mode = VIEWPORT_ANCHOR_MODE_ABSOLUTE;
  data_2.background = WMath::vec3( 0.92 );
  std::shared_ptr<Viewport> viewport_2
    ( new Viewport( data_2 ) );
  viewport_2->addScene( scene );

  
  renderer.addViewport( viewport_1 );
  renderer.addViewport( viewport_2 );

  std::shared_ptr<PhysicsManager> physics_manager( new PhysicsManager );
  XMLHelper::importPhysics( "physics_example", scene->getSceneGraph(), physics_manager );

  SceneEditor scene_editor( scene, resource_manager, physics_manager );
  scene_editor.initialize();

  auto t0 = std::chrono::high_resolution_clock::now();

  while(  window.isOpen() &&
          !active_input->isKeyPressed( GLFW_KEY_ESCAPE ) )
  {
    if( active_input->hasInput( std::set<int>{ GLFW_KEY_P }, PRESS ) )
      physics_manager->toggle();
    if( active_input->hasInput( std::set<int>{ GLFW_KEY_S }, PRESS ) )
      XMLHelper::exportScene( "test", &*scene );

    physics_manager->update();
    scene_editor.update();
    renderer.render();
    while( std::chrono::duration_cast< std::chrono::milliseconds >
      ( std::chrono::high_resolution_clock::now() - t0 ).count()
      < 16.6666666667 );
    t0 = std::chrono::high_resolution_clock::now();
  }

  return 0;
}
