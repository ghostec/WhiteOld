#include "Renderer/SceneEditor.h"

SceneEditor::SceneEditor( Scene* scene, MousePicking* mouse_picking, Shader& shader )
{
  this->shader = &shader;
  this->scene = scene;
  this->mouse_picking = mouse_picking;
  this->selected_model_instance = nullptr;
}

void SceneEditor::selectModelInstance()
{
  if( this->selected_model_instance != nullptr )
    this->selected_model_instance->getShaders( )->pop_back( );
    
  int id = this->mouse_picking->getIdForPosition( );

  if( id == 0 ) 
  {
    this->selected_model_instance = nullptr;
    return;
  }

  this->selected_model_instance = this->scene->getModelInstanceWithId( id );
  this->selected_model_instance->addShader( this->shader );
  this->scene->updateCamera();
}

void SceneEditor::move( )
{
  if( this->moves.ARROW_UP )
    WMath::translate( this->selected_model_instance->getTransform( ), WMath::vec3( 0.0f, 0.005f, 0.0f ) );
  if( this->moves.ARROW_DOWN )
    WMath::translate( this->selected_model_instance->getTransform( ), WMath::vec3( 0.0f, -0.005f, 0.0f ) );
}