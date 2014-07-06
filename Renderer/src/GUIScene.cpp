#include "Renderer/GUIScene.h"

void GUIScene::addGUIElement( std::string name,
  std::shared_ptr<GUIElement> gui_element )
{
  this->gui_elements[name] = gui_element;
}

void GUIScene::update()
{
  this->scene.getModels( )->clear();
  for( auto& el : this->gui_elements )
  {
    if( el.second->isDirty( ) ) el.second->update( );
    if( el.second->getGUIType() == DRAWNABLE )
    {
      this->scene.addModel( el.second->getModel() );
    }
  }
}