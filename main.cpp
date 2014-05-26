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
#include "Renderer/GUI.h"
#include "Input/Input.h"

int main()
{
  Window window;
  
  Input input( window.getWindow() );
  active_input = &input;

  Shader shader_standard( "standard" );
  Shader shader_wireframe( "wireframe" );
  shader_wireframe.setDrawMode( DM_WIRE );
  Shader shader_gui( "gui" );

  GUI gui( 20, 20, 1, 0.1 );

  ModelAsset model_asset( gui.vertices, gui.uvs, gui.normals, gui.elements );
  model_asset.setTexture( "chrome.png", &shader_gui );
  model_asset.addShader( &shader_gui );

  ModelInstance model_instance( &model_asset );
  WMath::rotate_x( model_instance.getTransform(), 180.0f );

  Camera camera(  WMath::vec3(-2.0f, 3.0f, 8.0f),
                  WMath::vec3(0.0f, 0.0f, 0.0f) );

  Light light(  WMath::vec3( 0.0f, 0.0f, -100.0f ),
                WMath::vec3( 1.0f, 1.0f, 1.0f ), 0.2f, 0.005f );

  Scene scene;
  scene.addModel( &model_instance );
  scene.addLight( &light );
  scene.setCamera( &camera );

  MousePicking mouse_picking;
  mouse_picking.setScene( &scene );
  SceneEditor scene_editor( &scene, &mouse_picking, shader_wireframe );

  input.registerObserver(  "CLICK",
                            std::bind( &SceneEditor::selectModelInstance, &scene_editor ),
                            "mouse_picking" );
  input.registerObserver( "ARROW_UP_PRESS",
    std::bind( [&] ( ) { scene_editor.moves.ARROW_UP = true; } ),
    "model" );
  input.registerObserver( "ARROW_UP_RELEASE",
    std::bind( [&] ( ) { scene_editor.moves.ARROW_UP = false; } ),
    "model" );

  input.registerObserver( "ARROW_DOWN_PRESS",
    std::bind( [&] ( ) { scene_editor.moves.ARROW_DOWN = true; } ),
    "model" );
  input.registerObserver( "ARROW_DOWN_RELEASE",
    std::bind( [&] ( ) { scene_editor.moves.ARROW_DOWN = false; } ),
    "model" );

  light.setPosition( WMath::vec3( -3.0f, 0.0f, 2.0f ) );

  Renderer renderer( &window, &scene_editor );
  renderer.setCurrentScene( &scene );

  while(  window.isOpen() &&
          !active_input->isKeyPressed( GLFW_KEY_ESCAPE ) )
  {
    scene_editor.move();
    renderer.render();
  }

  

  return 0;
}
