#include "Renderer/GUIScene.h"

void GUIScene::addGUIElement( std::shared_ptr<GUIElement> gui_element )
{
  this->gui_elements.push_back( gui_element );
}

void GUIScene::update()
{
  this->scene.getModels( )->clear();
  for( std::shared_ptr<GUIElement> gui_element : this->gui_elements )
  {
    this->scene.addModel( gui_element->getModel() );
  }
}