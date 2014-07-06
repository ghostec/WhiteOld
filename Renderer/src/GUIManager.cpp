#include "Renderer/GUIManager.h"

GUIManager::GUIManager( std::shared_ptr<ResourceManager> resource_manager )
{
  this->resource_manager = resource_manager;
  this->square_mesh.reset( new Mesh( "square.obj" ) );
  resource_manager->addMesh( "square", this->square_mesh );
}

void GUIManager::createGUIElement
  ( std::string name, WMath::vec2 dimensions, WMath::vec2 offset,
  WMath::vec2 offset_percent, GUIType gui_type )
{
  std::shared_ptr<GUIElement> gui_element( new GUIElement(
    this->square_mesh, dimensions, offset, offset_percent, gui_type ) );
  this->gui_element[name] = gui_element;
}

void GUIManager::createGUIElement
  ( std::string name, std::string parent, float parent_percent,
  WMath::vec2 offset, WMath::vec2 offset_percent, GUIType gui_type )
{
  std::shared_ptr<GUIElement> gui_parent = this->getGUIElement( parent );

  std::shared_ptr<GUIElement> gui_element
    ( new GUIElement( this->square_mesh, gui_parent, parent_percent, offset,
    offset_percent, gui_type ) );

  this->gui_element[name] = gui_element ;
}