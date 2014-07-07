#include "Renderer/GUIScene.h"

GUIScene::GUIScene( std::shared_ptr<GUIElement> container )
{
  this->container = container;
}

void GUIScene::update()
{
  this->scene.getModels()->clear();

  std::queue< std::shared_ptr<GUIElement> > el_queue; // BFS
  el_queue.push( this->container );

  while( !el_queue.empty() )
  {
    std::shared_ptr<GUIElement> el = el_queue.front();
    el_queue.pop();

    if( el->isDirty() ) el->update();
    if( el->getGUIType() == DRAWNABLE ) this->scene.addModel( el->getModel() );

    std::vector< std::shared_ptr<GUIElement> >* children =
      el->getChildren( );

    for( std::shared_ptr<GUIElement> el : *children ) el_queue.push( el );
  }
}