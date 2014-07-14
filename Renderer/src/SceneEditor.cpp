#include "Renderer/SceneEditor.h"

SceneEditor::SceneEditor( std::shared_ptr<Scene> scene )
{
  this->shader.reset( new Shader( "wireframe" ) );
  this->scene = scene;
  this->selected_model = nullptr;
  std::vector<Scene*> scenes = { &*scene };
  this->mouse_picking.setScenes( scenes );

  active_window->registerObserver( "RESIZE",
    std::bind( &MousePicking::reset, &mouse_picking ), "MousePicking" );
}

void SceneEditor::initialize()
{
  active_input->registerObserver
    ( "CLICK", std::bind( &SceneEditor::selectModel, this ),
    "SceneEditor::selectModel" );
}

void SceneEditor::selectModel()
{
  int x, y;
  active_input->getMousePos( &x, &y );
  std::shared_ptr<Model> model = mouse_picking.getIdForPosition( x, y );
  if( this->selected_model )
  {
    this->selected_model->setShader( this->old_selected_model_shader );
  }
  if( model ) 
  {    
    this->old_selected_model_shader = model->getShader();
    this->selected_model = model;
    this->selected_model->setShader( this->shader );
  }
}

void SceneEditor::update()
{
  Camera* camera = &*this->scene->getCamera();
  const std::set<int> keys = active_input->getKeys();
  for( int key : keys )
  {
    if( key == GLFW_KEY_UP )
    {
      WMath::translate( camera->getView(), WMath::vec3(0, -0.035, 0) );
    }
    else if( key == GLFW_KEY_DOWN )
    {
      WMath::translate( camera->getView( ), WMath::vec3( 0, 0.035, 0 ) );
    }
    else if( key == GLFW_KEY_LEFT )
    {
      WMath::translate( camera->getView( ), WMath::vec3( 0.035, 0, 0 ) );
    }
    else if( key == GLFW_KEY_RIGHT )
    {
      WMath::translate( camera->getView( ), WMath::vec3( -0.035, 0, 0 ) );
    }
  }
}