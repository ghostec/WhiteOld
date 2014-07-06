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
#include "Renderer/Helpers/XMLHelper.h"
#include "Input/Input.h"

int main()
{
  Window window;
  
  Input input( window.getWindow() );
  active_input = &input;

  std::shared_ptr<ResourceManager> resource_manager( new ResourceManager );

  std::shared_ptr<Mesh> mesh( new Mesh( "square.obj" ) );
  std::shared_ptr<Shader> shader( new Shader( "gui" ) );
  std::shared_ptr<Texture> texture( new Texture( "circle.png" ) );
  GUIState gui_state = { shader, texture };

  GUIScene gui_scene;

  std::shared_ptr<GUIElement> gui_window( new GUIElement( mesh, nullptr, CONTAINER ) );
  std::shared_ptr<GUIElement> gui_element( new GUIElement( mesh, gui_window, DRAWNABLE ) );
  gui_window->addChild( gui_element );
  gui_element->setState( "normal", gui_state );
  gui_element->setState( "normal" );
  gui_scene.addGUIElement( "window", gui_window );
  gui_scene.addGUIElement( "element", gui_element );

  gui_window->setParentPercent( 0.25 );

  //gui_window->setParentPercent( 0.5 );

  Renderer renderer( &window );
  renderer.addScene( gui_scene.getScene() );

  auto t0 = std::chrono::high_resolution_clock::now();

  while(  window.isOpen() &&
          !active_input->isKeyPressed( GLFW_KEY_ESCAPE ) )
  {
    gui_scene.update();
    renderer.render();
    while( std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::high_resolution_clock::now() - t0 ).count() < 16.6666666667 );
    t0 = std::chrono::high_resolution_clock::now();
  }

  return 0;
}
