#include "Renderer/GUIManager.h"

GUIManager::GUIManager( std::shared_ptr<ResourceManager> resource_manager )
{
  this->resource_manager = resource_manager;
  this->square_mesh.reset( new Mesh( "square.obj" ) );
  this->resource_manager->addMesh( "square", this->square_mesh );
}

void GUIManager::createGUIScene( std::string name )
{
  std::shared_ptr<GUIElement> gui_window
    ( new GUIElement( this->square_mesh, nullptr, CONTAINER ) );

  std::string window_name = name + "_window";

  this->gui_element[window_name] = gui_window;

  std::shared_ptr<GUIScene> gui_scene( new GUIScene( gui_window, name ) );
  this->gui_scene[name] = gui_scene;
}

void GUIManager::createGUIElement
  ( std::string name, std::string scene_name, std::string parent_name,
  GUIType gui_type )
{
  std::shared_ptr<GUIElement> gui_parent;
  if( parent_name.empty() ) 
  {
    std::string window_name = scene_name + "_window";
    gui_parent = this->gui_element[window_name];
  }
  else gui_parent = this->gui_element[parent_name];

  std::shared_ptr<GUIElement> gui_element
    ( new GUIElement( this->square_mesh, gui_parent, gui_type ) );

  this->gui_element[name] = gui_element;
  gui_parent->addChild( gui_element );
}