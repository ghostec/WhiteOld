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
#include "Renderer/GUIManager.h"
#include "Renderer/GUIElement.h"
#include "Renderer/GUIScene.h"
#include "Renderer/Effect.h"
#include "Renderer/EffectsManager.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/Helpers/XMLAssets.h"
#include "Renderer/Helpers/XMLGUIScene.h"
#include "Input/Input.h"

int main()
{
  Window window;
  
  Input input( window.getWindow() );
  active_input = &input;

  std::shared_ptr<ResourceManager> resource_manager( new ResourceManager );
  GUIManager gui_manager( resource_manager );
  XMLHelper::importAssets( "assets", resource_manager );
  XMLHelper::importGUIScene( "gui", &gui_manager );

  std::shared_ptr<GUIScene> gui_scene = gui_manager.getGUIScene( "gui_scene" );

  Renderer renderer( &window );
  renderer.addScene( gui_scene->getScene() );

  auto t0 = std::chrono::high_resolution_clock::now();

  while(  window.isOpen() &&
          !active_input->isKeyPressed( GLFW_KEY_ESCAPE ) )
  {
    gui_scene->update();
    renderer.render();
    while( std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::high_resolution_clock::now() - t0 ).count() < 16.6666666667 );
    t0 = std::chrono::high_resolution_clock::now();
  }

  return 0;
}
