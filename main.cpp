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
#include "Renderer/MousePicking.h"
#include "Input/Input.h"

void test( MousePicking* mouse_picking, std::shared_ptr<ResourceManager> resource_manager )
{
  std::shared_ptr<Model> model;
  std::shared_ptr<Shader> shader = resource_manager->getShader( "standard2" );
  int x, y;
  active_input->getMousePos( &x, &y );
  model = mouse_picking->getIdForPosition( x, y );
  if( model ) model->setShader( shader );
}

int main()
{
  Window window( WMath::vec2( 800, 600 ) );
  active_window = &window;
  
  Input input( window.getWindow() );
  active_input = &input;

  std::shared_ptr<ResourceManager> resource_manager( new ResourceManager );

  XMLHelper::importAssets( "assets", resource_manager );
  Scene scene = XMLHelper::importScene( "example", resource_manager );

  Renderer renderer( &window );
  renderer.addScene( &scene );

  MousePicking mouse_picking;
  std::vector<Scene*> scenes = { &scene };
  mouse_picking.setScenes( scenes );

  input.registerObserver( "CLICK", std::bind( test, &mouse_picking, resource_manager ), "test" );

  auto t0 = std::chrono::high_resolution_clock::now();

  while(  window.isOpen() &&
          !active_input->isKeyPressed( GLFW_KEY_ESCAPE ) )
  {
    renderer.render();
    while( std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::high_resolution_clock::now() - t0 ).count() < 16.6666666667 );
    t0 = std::chrono::high_resolution_clock::now();
  }

  return 0;
}
