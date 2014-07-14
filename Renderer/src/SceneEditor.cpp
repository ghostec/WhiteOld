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

  this->state = NORMAL;
}

void SceneEditor::initialize()
{
  active_input->registerObserver
    ( "MOUSE_SCROLL", std::bind( &SceneEditor::mouseScroll, this ),
    "SceneEditor::selectModel" );
}

void SceneEditor::selectModel()
{
  std::shared_ptr<Model> model = mouse_picking.pick();
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

bool isSubset( std::set<int> subset, std::set<int> set )
{
  for( std::set<int>::iterator it = subset.begin(); it != subset.end(); ++it )
  {
    bool e = false;
    for( int j = 0; j < set.size(); j++ )
    {
      if( set.find( *it ) != set.end() )
      {
        e = true;
        break;
      }
    }
    if( e == false ) return false;
  }
  return true;
}

void SceneEditor::mouseScroll()
{
  Camera* camera = &*this->scene->getCamera();
  const WMath::vec2 scroll_offset = active_input->getMouseScroll();
  if( scroll_offset[1] > 0 )
  {
    WMath::translate( camera->getView(), WMath::vec3( 0, 0, 0.1 ) );
  }
  else
  {
    WMath::translate( camera->getView(), WMath::vec3( 0, 0, -0.1 ) );
  }
}

void rotateCamera( Camera* camera, SceneEditor* scene_editor )
{
  static WMath::vec2 last_cursor_pos;
  if( scene_editor->getState() != ROTATING_CAMERA )
  {
    last_cursor_pos = active_input->getMousePos();
    scene_editor->setState( ROTATING_CAMERA );
  }
  else
  {
    WMath::vec2 cursor_pos = active_input->getMousePos();
    WMath::vec2 diff = cursor_pos - last_cursor_pos;

    std::cout << diff[0] << " " << diff[1] << std::endl;

    WMath::translate( camera->getView( ), WMath::vec3( diff[0] / 100.0f, diff[1] / 100.0f, 0 ) );
    WMath::rotate_y( camera->getView(), -diff[0] / 10.0f );
    WMath::rotate_x( camera->getView(), -diff[1] / 10.0f );
    last_cursor_pos = cursor_pos;
  }
}

void SceneEditor::update()
{
  Camera* camera = &*this->scene->getCamera();
  const std::set<int> input = active_input->getInput();
  if( isSubset( std::set<int>{ GLFW_KEY_UP }, input ) )
  {
    WMath::translate( camera->getView(), WMath::vec3(0, -0.04, 0) );
  }
  else if( isSubset( std::set<int>{ GLFW_KEY_DOWN }, input ) )
  {
    WMath::translate( camera->getView(), WMath::vec3( 0, 0.04, 0 ) );
  }
  else if( isSubset( std::set<int>{ GLFW_KEY_LEFT }, input ) )
  {
    WMath::translate( camera->getView(), WMath::vec3( 0.04, 0, 0 ) );
  }
  else if( isSubset( std::set<int>{ GLFW_KEY_RIGHT }, input ) )
  {
    WMath::translate( camera->getView(), WMath::vec3( -0.04, 0, 0 ) );
  }

  if( isSubset( std::set<int>{ GLFW_KEY_LEFT_ALT, GLFW_MOUSE_BUTTON_1 }, input ) )
  {
    rotateCamera( camera, this );
  }
  else 
  {
    if( isSubset( std::set<int>{ GLFW_MOUSE_BUTTON_1 }, input ) )
    {
      this->selectModel( );
    }
    this->state = NORMAL; 
  }
}