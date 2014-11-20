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
#include "Renderer/GUIElement.h"
#include "Renderer/GUIScene.h"
#include "Renderer/GUITextManager.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/Helpers/XMLAssets.h"
#include "Renderer/Helpers/XMLScene.h"
#include "Renderer/Helpers/XMLGUIScene.h"
#include "Renderer/Helpers/CameraHelper.h"
#include "Renderer/MousePicking.h"
#include "Renderer/SceneGraph.h"
#include "Renderer/SGNode.h"
#include "Renderer/Containable.h"
#include "Renderer/Heightmap.h"
#include "Input/Input.h"
#include "Physics/PhysicsManager.h"
#include "Physics/Helpers/XMLPhysics.h"

int main()
{
	Window window(WMath::vec2(1200, 900));
	active_window = &window;

	Input input(window.getWindow());
	active_input = &input;

	std::shared_ptr<ResourceManager> resource_manager(new ResourceManager);

	XMLHelper::importAssets("assets", resource_manager);
	std::shared_ptr<Scene> scene =
		std::make_shared<Scene>
		(XMLHelper::importScene("example", resource_manager));
	Camera* camera = &*scene->getCamera();
	CameraHelper::normalCamera(camera, 1);
	WMath::translate(camera->getView(), WMath::vec3(-1, -4, -13));

	Renderer renderer(&window);

	ContainableData viewport_window_data;
	viewport_window_data.mode = CONTAINABLE_MODE_HSPLIT;
	viewport_window_data.mode_data.hsplit.side = CONTAINABLE_SIDE_TOP;
	viewport_window_data.mode_data.hsplit.dimension_mode = CONTAINABLE_DIMENSIONS_MODE_ABSOLUTE;
	viewport_window_data.mode_data.hsplit.size = 100;
	std::shared_ptr<Viewport> viewport_window(new Viewport(viewport_window_data));

	ContainableData viewport_window_top_data;
	viewport_window_top_data.mode = CONTAINABLE_MODE_FULL;
	viewport_window_top_data.background = WMath::vec3(0.0f);
	std::shared_ptr<Viewport> viewport_window_top(new Viewport(viewport_window_top_data));

	ContainableData viewport_window_bottom_data;
	viewport_window_bottom_data.mode = CONTAINABLE_MODE_VSPLIT;
	viewport_window_bottom_data.mode_data.vsplit.side = CONTAINABLE_SIDE_RIGHT;
	viewport_window_bottom_data.mode_data.vsplit.dimension_mode = CONTAINABLE_DIMENSIONS_MODE_ABSOLUTE;
	viewport_window_bottom_data.mode_data.vsplit.size = 260;
	std::shared_ptr<Viewport> viewport_window_bottom(new Viewport(viewport_window_bottom_data));

	ContainableData viewport_window_left_data;
	viewport_window_left_data.mode = CONTAINABLE_MODE_FULL;
	viewport_window_left_data.background = WMath::vec3(0.9f);
	std::shared_ptr<Viewport> viewport_window_left(new Viewport(viewport_window_left_data));

	ContainableData viewport_window_right_data;
	viewport_window_right_data.mode = CONTAINABLE_MODE_FULL;
	viewport_window_right_data.background = WMath::vec3(1.0f);
	std::shared_ptr<Viewport> viewport_window_right(new Viewport(viewport_window_right_data));

	viewport_window->setLeftChild(viewport_window_top);
	viewport_window->setRightChild(viewport_window_bottom);
	viewport_window_bottom->setLeftChild(viewport_window_left);
	viewport_window_bottom->setRightChild(viewport_window_right);

	viewport_window_left->addScene(scene);

	renderer.setViewport(viewport_window);

	MousePicking mouse_picking;
	active_mouse_picking = &mouse_picking;
	active_mouse_picking->setViewport(viewport_window);

	std::shared_ptr<PhysicsManager> physics_manager(new PhysicsManager);
	XMLHelper::importPhysics("physics_example", scene->getSceneGraph(), physics_manager);

	SceneEditor scene_editor(scene, resource_manager, physics_manager);
	scene_editor.initialize();

	ContainableData ge_position_data;
	ge_position_data.mode = CONTAINABLE_MODE_BOX;
	ge_position_data.mode_data.box.anchor_position = CONTAINABLE_ANCHOR_TOP_LEFT;
	ge_position_data.mode_data.box.anchor_mode = CONTAINABLE_ANCHOR_MODE_ABSOLUTE;
	ge_position_data.mode_data.box.anchor_x = 20;
	ge_position_data.mode_data.box.anchor_y = 20;
	ge_position_data.mode_data.box.dimensions_mode = CONTAINABLE_DIMENSIONS_MODE_ABSOLUTE;
	ge_position_data.mode_data.box.smaller_dimension = 72.0f;
	ge_position_data.mode_data.box.aspect_ratio = 220.0f / 72.0f;
	std::shared_ptr<GUIElement> ge_position
		( new GUIElement( "ge_position", ge_position_data ) );

  ContainableData ge_position_box_data;
  ge_position_box_data.mode = CONTAINABLE_MODE_HSPLIT;
  ge_position_box_data.mode_data.hsplit.side = CONTAINABLE_SIDE_TOP;
  ge_position_box_data.mode_data.hsplit.dimension_mode = CONTAINABLE_DIMENSIONS_MODE_ABSOLUTE;
  ge_position_box_data.mode_data.hsplit.size = 36.0f;
  std::shared_ptr<GUIElement> ge_position_box
    ( new GUIElement( "ge_position_box", ge_position_box_data ) );

  ContainableData ge_position_x_yz_data;
  ge_position_x_yz_data.mode = CONTAINABLE_MODE_VSPLIT;
  ge_position_x_yz_data.mode_data.hsplit.side = CONTAINABLE_SIDE_LEFT;
  ge_position_x_yz_data.mode_data.hsplit.dimension_mode = CONTAINABLE_DIMENSIONS_MODE_ABSOLUTE;
  ge_position_x_yz_data.mode_data.hsplit.size = 220.0f / 3.0f;
  std::shared_ptr<GUIElement> ge_position_x_yz
    ( new GUIElement( "ge_position_x_yz", ge_position_x_yz_data ) );

  ContainableData ge_position_y_z_data;
  ge_position_y_z_data.mode = CONTAINABLE_MODE_VSPLIT;
  ge_position_y_z_data.mode_data.hsplit.side = CONTAINABLE_SIDE_LEFT;
  ge_position_y_z_data.mode_data.hsplit.dimension_mode = CONTAINABLE_DIMENSIONS_MODE_ABSOLUTE;
  ge_position_y_z_data.mode_data.hsplit.size = 220.0f / 3.0f;
  std::shared_ptr<GUIElement> ge_position_y_z
    ( new GUIElement( "ge_position_y_z", ge_position_y_z_data ) );

  std::shared_ptr<GUITextManager> gui_text_manager( new GUITextManager() );

  std::shared_ptr<GUIText> gt_position = gui_text_manager->makeGUIText( "position_label", "liberation", 36.0f, "POSITION", nullptr, viewport_window_right );
  std::shared_ptr<GUIText> gt_position_x = gui_text_manager->makeGUIText( "position_x", "liberation", 36.0f, "X", nullptr, viewport_window_right );
  std::shared_ptr<GUIText> gt_position_y = gui_text_manager->makeGUIText( "position_y", "liberation", 36.0f, "Y", nullptr, viewport_window_right );
  std::shared_ptr<GUIText> gt_position_z = gui_text_manager->makeGUIText( "position_z", "liberation", 36.0f, "Z", nullptr, viewport_window_right );

  ge_position->setLeftChild( ge_position_box );
  ge_position_box->setLeftChild( gt_position->getGUIElement() );
  ge_position_box->setRightChild( ge_position_x_yz );
  ge_position_x_yz->setLeftChild( gt_position_x->getGUIElement() );
  ge_position_x_yz->setRightChild( ge_position_y_z );
  ge_position_y_z->setLeftChild( gt_position_y->getGUIElement() );
  ge_position_y_z->setRightChild( gt_position_z->getGUIElement() );

	std::shared_ptr<GUIScene> gui_scene(new GUIScene("GUIScene"));
	gui_scene->setViewport( viewport_window_right );
	gui_scene->setRootGUIElement( ge_position );

	viewport_window_right->addScene( gui_scene->getScene() );

  std::shared_ptr<Heightmap> heightmap( new Heightmap( "../assets/images/heightmap.jpg" ) );
  std::shared_ptr<Model> hm_model( new Model( "heightmap", heightmap->getMesh() ) );
  std::shared_ptr<Shader> hm_shader( new Shader( "standard" ) );
  std::shared_ptr<Texture> hm_texture( new Texture( "wooden-crate.jpg" ) );
  hm_model->setShader( hm_shader );
  hm_model->setTexture( hm_texture );
  std::shared_ptr<SGNode> hm_node( new SGNode( "heightmap", hm_model ) );
  scene->getSceneGraph()->getRootSGNode()->addChild( hm_node );
  SGNodeWorldTransform hm_transform;
  hm_transform.data.position = WMath::vec3( 0.0f, 1.0f, 0.0f );
  hm_transform.data.scale = WMath::vec3( 10.0f, 2.0f, 10.0f );
  hm_node->setWorldTransform( hm_transform );

  std::shared_ptr<Mesh> mmm( new Mesh( "cube.obj" ) );
  std::shared_ptr<Model> moo( new Model( "cube", mmm ) );
  std::shared_ptr<SGNode> sss( new SGNode( "cube", moo ) );
  moo->setShader( hm_shader );
  //scene->getSceneGraph()->getRootSGNode()->addChild( sss );

  //gui_scene->setRootGUIElement( gui_text->getGUIElement() );

  ApplicationHelper::JobDispatcher job_dispatcher;
  ApplicationHelper::g_job_dispatcher = &job_dispatcher;

  gt_position->getGUIElement()->getModel()->getModelData()->set( "color", WMath::vec4( 1.0f, 0.0f, 0.0f, 1.0f ) );
  gt_position_x->getGUIElement()->getModel()->getModelData()->set( "color", WMath::vec4( 1.0f, 1.0f, 0.0f, 1.0f ) );
  gt_position_y->getGUIElement()->getModel()->getModelData()->set( "color", WMath::vec4( 1.0f, 0.0f, 0.0f, 1.0f ) );
  gt_position_z->getGUIElement()->getModel()->getModelData()->set( "color", WMath::vec4( 1.0f, 0.0f, 0.0f, 1.0f ) );

	auto t0 = std::chrono::high_resolution_clock::now();

	while (window.isOpen() &&
		!active_input->isKeyPressed(GLFW_KEY_ESCAPE))
	{
		if (active_input->hasInput(std::set<int>{ GLFW_KEY_P }, PRESS))
			physics_manager->toggle();
		if (active_input->hasInput(std::set<int>{ GLFW_KEY_S }, PRESS))
			XMLHelper::exportScene("test", &*scene);

    RendererHelper::updateViewport( &*viewport_window );
    physics_manager->update();
    gui_text_manager->update();
    gui_scene->update(); 
		scene_editor.update();
		renderer.render();
    ApplicationHelper::g_job_dispatcher->execute();

		while (std::chrono::duration_cast< std::chrono::milliseconds >
			(std::chrono::high_resolution_clock::now() - t0).count()
			< 16.6666666667);
		t0 = std::chrono::high_resolution_clock::now();
	}

	return 0;
}