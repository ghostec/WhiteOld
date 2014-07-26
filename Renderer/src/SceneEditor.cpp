#include "Renderer/SceneEditor.h"

SceneEditor::SceneEditor( std::shared_ptr<Scene> scene,
  std::shared_ptr<ResourceManager> resource_manager )
{
  this->shader.reset( new Shader( "wireframe" ) );
  this->scene = scene;
  this->selected_model = nullptr;
  std::vector<Scene*> scenes = { &*scene };
  this->mouse_picking.setScenes( scenes );
  this->resource_manager = resource_manager;
  XMLHelper::importAssets( "assets_SceneEditor", resource_manager );

  this->cant_select.insert( resource_manager->getModel( "arrow" ) );

  active_window->registerObserver( "RESIZE",
    std::bind( &MousePicking::reset, &mouse_picking ), "MousePicking" );

  this->state = NO_SELECTION;
}

void SceneEditor::initialize()
{
  active_input->registerObserver
    ( "MOUSE_SCROLL", std::bind( &SceneEditor::mouseScroll, this ),
    "SceneEditor::selectModel" );
}

void updateMoveArrows( SceneEditor* scene_editor,
  ResourceManager* resource_manager )
{
  Model* model = &*scene_editor->getSelectedModel();
  Model* arrow = &*resource_manager->getModel( "arrow" );
  arrow->resetTransform();
  *arrow->getTranslateM() = *model->getTranslateM();
  WMath::vec3 d =
    0.5f * ( model->getDimensions() + arrow->getDimensions() );
  WMath::rotate_z( arrow->getScaleM(), -90.0f );
  WMath::translate( arrow->getTranslateM(), WMath::vec3( d[1], 0, 0 ) );
}

void hideMoveArrows( std::shared_ptr<Scene> scene,
  std::shared_ptr<ResourceManager> resource_manager )
{
  std::shared_ptr<Model> arrow = resource_manager->getModel( "arrow" );
  scene->removeModel( arrow );
}

void showMoveArrows( SceneEditor* scene_editor,
  ResourceManager* resource_manager )
{
  /*
  std::shared_ptr<Model> arrow = resource_manager->getModel( "arrow" );
  arrow->resetTransform();
  WMath::vec3 d = 
    0.5f * ( selected_model->getDimensions() + arrow->getDimensions() );
  WMath::translate( arrow->getTranslateM(), WMath::vec3( 0, d[1], 0 ) );
  scene->addModel( arrow );
  */

  std::shared_ptr<Model> arrow = resource_manager->getModel( "arrow" );
  scene_editor->getScene()->addModel( arrow );
  updateMoveArrows( scene_editor, resource_manager );
}

template<typename T>
bool isSubset( std::set<T> subset, std::set<T> set )
{
  for( typename std::set<T>::iterator it = subset.begin(); it != subset.end(); ++it )
  {
    bool e = false;
    for( int j = 0; j < set.size( ); j++ )
    {
      if( set.find( *it ) != set.end( ) )
      {
        e = true;
        break;
      }
    }
    if( e == false ) return false;
  }
  return true;
}

void SceneEditor::moveSelectedModel()
{
  static WMath::vec2 last_cursor_pos;
  if( this->state != MOVING_MODEL )
  {
    last_cursor_pos = active_input->getMousePos();
    this->state = MOVING_MODEL;
  }
  else
  {
    WMath::vec2 cursor_pos = active_input->getMousePos();
    WMath::vec2 diff = cursor_pos - last_cursor_pos;

    WMath::translate( this->selected_model->getTranslateM(), WMath::vec3( diff[0] / 100.0f, 0, 0 ) );
    updateMoveArrows( this, &*this->resource_manager );
    last_cursor_pos = cursor_pos;
  }
}

void SceneEditor::selectModel( std::shared_ptr<Model> model )
{
  if( this->selected_model )
  {
    this->selected_model->setShader( this->old_selected_model_shader );
    hideMoveArrows( this->scene, this->resource_manager );
    this->state = NO_SELECTION;
  }
  if( model )
  {
    this->old_selected_model_shader = model->getShader( );
    this->selected_model = model;
    this->selected_model->setShader( this->shader );
    showMoveArrows( this, &*this->resource_manager );
    this->state = MODEL_SELECTED;
  } 
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

    WMath::translate( camera->getView( ), WMath::vec3( diff[0] / 100.0f, diff[1] / 100.0f, 0 ) );
    WMath::rotate_y( camera->getView(), -diff[0] / 10.0f );
    WMath::rotate_x( camera->getView(), -diff[1] / 10.0f );
    last_cursor_pos = cursor_pos;
  }
}

void SceneEditor::update()
{
  Camera* camera = &*this->scene->getCamera();
  std::set<int> input = active_input->getInput();

  if( this->state == NO_SELECTION || this->state == MODEL_SELECTED )
  {
    if( isSubset( std::set<int>{ GLFW_KEY_UP }, input ) )
    {
      WMath::translate( camera->getView(), WMath::vec3( 0, -0.04, 0 ) );
    }
    else if( isSubset<int>( std::set<int>{ GLFW_KEY_DOWN }, input ) )
    {
      WMath::translate( camera->getView(), WMath::vec3( 0, 0.04, 0 ) );
    }
    else if( isSubset<int>( std::set<int>{ GLFW_KEY_LEFT }, input ) )
    {
      WMath::translate( camera->getView(), WMath::vec3( 0.04, 0, 0 ) );
    }
    else if( isSubset<int>( std::set<int>{ GLFW_KEY_RIGHT }, input ) )
    {
      WMath::translate( camera->getView(), WMath::vec3( -0.04, 0, 0 ) );
    }
    else if( isSubset<int>( std::set<int>{ GLFW_KEY_LEFT_ALT, GLFW_MOUSE_BUTTON_1 }, input ) )
    {
      rotateCamera( camera, this );
    }
    else if( isSubset<int>( std::set<int>{ GLFW_MOUSE_BUTTON_1 }, input ) )
    {
      std::shared_ptr<Model> model = mouse_picking.pick( );
      if( isSubset< std::shared_ptr<Model> >
        ( std::set< std::shared_ptr<Model> >{ model }, this->cant_select ) )
      {
        if( model == resource_manager->getModel( "arrow" ) )
        {
          this->moveSelectedModel();
        }
      }
      else this->selectModel( model );
    }
  }
  else if( this->state == ROTATING_CAMERA )
  {
    if( isSubset<int>( std::set<int>{ GLFW_KEY_LEFT_ALT, GLFW_MOUSE_BUTTON_1 }, input ) )
    {
      rotateCamera( camera, this );
    }
    else
    {
      if( this->selected_model ) this->state = MODEL_SELECTED;
      else this->state = NO_SELECTION;
    }
  }
  else if( this->state == MOVING_MODEL )
  {
    if( isSubset<int>( std::set<int>{ GLFW_MOUSE_BUTTON_1 }, input ) )
    {
      this->moveSelectedModel( );
    }
    else
    {
      this->state = MODEL_SELECTED;
    }
  }
}
