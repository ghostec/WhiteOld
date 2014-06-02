#include "Renderer/GUIScene.h"

GUIScene::GUIScene( std::shared_ptr<Scene> scene )
{
  this->scene = scene;
  this->mouse_picking.setScene( this->scene );
}

void GUIScene::addGUIInstance( std::shared_ptr<GUIInstance> gui_instance )
{
  this->gui_instances.push_back( gui_instance );
  this->scene->addModel( gui_instance->getModelInstance() );
}

void GUIScene::pollEvents()
{
  int x, y;
  active_input->getMousePos( &x, &y );
  int instance_id = this->mouse_picking.getIdForPosition( x, y );
  
  for( std::shared_ptr<GUIInstance> gui_instance : this->gui_instances )
  {
    if( gui_instance->getModelInstance()->getPickingId() == instance_id )
    {
      //gui_instance->setState( GUI_HOVER );
    }
    else
    {
      //gui_instance->setState( GUI_NORMAL );
    }
  }
}