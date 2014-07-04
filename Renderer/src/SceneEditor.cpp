#include "Renderer/SceneEditor.h"

SceneEditor::SceneEditor( std::shared_ptr<Scene> scene, std::shared_ptr<MousePicking> mouse_picking, std::shared_ptr<Shader> shader )
{
  this->shader = shader;
  this->scene = scene;
  this->mouse_picking = mouse_picking;
  this->selected_model_instance = nullptr;
}

void SceneEditor::selectModelInstance()
{
  if( this->selected_model_instance != nullptr )
  {
    ;
    // remove wireframe shader
  }

  int x, y;
  active_input->getMousePos( &x, &y );
    
  int id = this->mouse_picking->getIdForPosition( x, y );

  if( id == 0 ) 
  {
    this->selected_model_instance = nullptr;
    return;
  }

  this->selected_model_instance->setShader( this->shader );
  this->scene->updateCamera();
}

void SceneEditor::move( )
{ 
  if( this->moves.ARROW_UP )
    WMath::translate( this->selected_model_instance->getTranslateM( ), WMath::vec3( 0.0f, 0.005f, 0.0f ) );
  if( this->moves.ARROW_DOWN )
    WMath::translate( this->selected_model_instance->getTranslateM( ), WMath::vec3( 0.0f, -0.005f, 0.0f ) );
}