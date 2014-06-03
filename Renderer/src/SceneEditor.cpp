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
    std::vector< std::shared_ptr<Shader> >* shaders = this->selected_model_instance->getShaders( );
    for( std::shared_ptr<Shader> shader : *shaders )
    {
      shaders
      ->erase(  std::remove_if( shaders->begin( ),
                              shaders->end( ),
                              [&] ( std::shared_ptr<Shader> shader )
                              { return shader->getName() == "wireframe"; } ),
                shaders->end() );
    }
  }

  int x, y;
  active_input->getMousePos( &x, &y );
    
  int id = this->mouse_picking->getIdForPosition( x, y );

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
    WMath::translate( this->selected_model_instance->getTranslateM( ), WMath::vec3( 0.0f, 0.005f, 0.0f ) );
  if( this->moves.ARROW_DOWN )
    WMath::translate( this->selected_model_instance->getTranslateM( ), WMath::vec3( 0.0f, -0.005f, 0.0f ) );
}