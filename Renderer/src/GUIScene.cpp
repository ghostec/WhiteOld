#include "Renderer/GUIScene.h"

GUIScene::GUIScene( Scene* scene )
{
  this->scene = scene;
  this->mouse_picking.setScene( this->scene );
}

void GUIScene::addGUIInstance( GUIInstance* gui_instance )
{
  this->gui_instances.push_back( gui_instance );
  this->scene->addModel( gui_instance->getModelInstance() );
}

void GUIScene::pollEvents()
{
  int x, y;
  active_input->getMousePos( &x, &y );
  int instance_id = this->mouse_picking.getIdForPosition( x, y );
  
  for( GUIInstance* gui_instance : this->gui_instances )
  {
    if( gui_instance->getModelInstance()->getPickingId() == instance_id )
    {
      gui_instance->setState( GUI_HOVER );
    }
    else
    {
      gui_instance->setState( GUI_NORMAL );
    }
  }
}