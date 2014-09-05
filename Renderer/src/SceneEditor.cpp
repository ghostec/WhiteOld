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

  this->cant_select
    .insert( resource_manager->getModel( "SceneEditor_arrow_x" ) );
  this->cant_select
    .insert( resource_manager->getModel( "SceneEditor_arrow_y" ) );
  this->cant_select
    .insert( resource_manager->getModel( "SceneEditor_arrow_z" ) );

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
  WMath::vec3 model_dimensions = model->getDimensions();

  Model* arrow_x = &*resource_manager->getModel( "SceneEditor_arrow_x" );
  arrow_x->resetTransform();

  Model* arrow_y = &*resource_manager->getModel( "SceneEditor_arrow_y" );
  arrow_y->resetTransform();

  Model* arrow_z = &*resource_manager->getModel( "SceneEditor_arrow_z" );
  arrow_z->resetTransform();

  *arrow_x->getTranslateM() = *arrow_y->getTranslateM() =
    *arrow_z->getTranslateM() = *model->getTranslateM();
  float dx = 0.5f * ( model_dimensions[0] + arrow_x->getDimensions()[0] );
  WMath::rotate_z( arrow_x->getRotateM(), -90.0f );
  WMath::translate( arrow_x->getTranslateM(), WMath::vec3( dx, 0, 0 ) );
  float dy = 0.5f * ( model_dimensions[1] + arrow_y->getDimensions()[1] );
  WMath::translate( arrow_y->getTranslateM(), WMath::vec3( 0, dy, 0 ) );
  float dz = 0.5f * ( model_dimensions[2] + arrow_x->getDimensions()[2] );
  WMath::rotate_x( arrow_z->getRotateM(), 90.0f );
  WMath::translate( arrow_z->getTranslateM(), WMath::vec3( 0, 0, dz ) );
}

void hideMoveArrows( std::shared_ptr<Scene> scene,
  std::shared_ptr<ResourceManager> resource_manager )
{
  scene->removeModel( resource_manager->getModel( "SceneEditor_arrow_x" ) );
  scene->removeModel( resource_manager->getModel( "SceneEditor_arrow_y" ) );
  scene->removeModel( resource_manager->getModel( "SceneEditor_arrow_z" ) );
}

void showMoveArrows( SceneEditor* scene_editor,
  ResourceManager* resource_manager )
{
  std::shared_ptr<Model> arrow;

  arrow = resource_manager->getModel( "SceneEditor_arrow_x" );
  scene_editor->getScene()->addModel( arrow );
  arrow = resource_manager->getModel( "SceneEditor_arrow_y" );
  scene_editor->getScene()->addModel( arrow );
  arrow = resource_manager->getModel( "SceneEditor_arrow_z" );
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

void SceneEditor::moveSelectedModel( SceneEditorAxis direction )
{
  static WMath::vec2 last_cursor_pos;
  static SceneEditorAxis dir;

  if( this->state != MOVING_MODEL )
  {
    dir = direction;
    last_cursor_pos = active_input->getMousePos();
    this->state = MOVING_MODEL;
  }
  else
  {
    WMath::vec2 cursor_pos = active_input->getMousePos();
    WMath::vec2 diff = cursor_pos - last_cursor_pos;

    WMath::vec3 dT(0);

    float value = (diff[0] - diff[1]) / 100.0f;
    if( dir == SEA_X ) dT[0] = value;
    else if( dir == SEA_Y ) dT[1] = value;
    else if( dir == SEA_Z ) dT[2] = -value;

    WMath::translate( this->selected_model->getTranslateM(), dT );
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
    WMath::translate( camera->getView(), WMath::vec3( 0, 0, 0.2 ) );
  }
  else
  {
    WMath::translate( camera->getView(), WMath::vec3( 0, 0, -0.2 ) );
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

    WMath::translate( camera->getView( ), WMath::vec3( diff[0] / 50.0f, diff[1] / 50.0f, 0 ) );
    WMath::rotate_y( camera->getView(), -diff[0] / 10.0f );
    WMath::rotate_x( camera->getView(), -diff[1] / 10.0f );
    last_cursor_pos = cursor_pos;
  }
}

void SceneEditor::update_NO_SELECTION__MODEL_SELECTED()
{
  Camera* camera = &*this->scene->getCamera();
  std::set<int> input = active_input->getInput();
  static std::shared_ptr<Model> model_hovered = nullptr;
  static std::shared_ptr<Texture> texture_hovered = nullptr;

  if( model_hovered )
  {
    model_hovered->setTexture( texture_hovered );
    model_hovered = nullptr; texture_hovered = nullptr;
  }

  std::shared_ptr<Model> model = mouse_picking.pick();

  if( model == resource_manager->getModel( "SceneEditor_arrow_x" ) || 
    model == resource_manager->getModel( "SceneEditor_arrow_y" ) || 
    model == resource_manager->getModel( "SceneEditor_arrow_z" ) )
  {
    model_hovered = model;
    texture_hovered = model->getTexture();
    model->setTexture( resource_manager->getTexture( "yellow" ) );
  }

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
    if( isSubset< std::shared_ptr<Model> >
        ( std::set< std::shared_ptr<Model> >{ model }, this->cant_select ) )
    {
      if( model == resource_manager->getModel( "SceneEditor_arrow_x" ) )
      {
        this->moveSelectedModel( SEA_X );
        model->setTexture( resource_manager->getTexture( "yellow" ) );
      }
      else if( model == resource_manager->getModel( "SceneEditor_arrow_y" ) )
      {
        this->moveSelectedModel( SEA_Y );
        model->setTexture( resource_manager->getTexture( "yellow" ) );
      }
      else if( model == resource_manager->getModel( "SceneEditor_arrow_z" ) )
      {
        this->moveSelectedModel( SEA_Z );
        model->setTexture( resource_manager->getTexture( "yellow" ) );
      }
    }
    else this->selectModel( model );
  }
}

void SceneEditor::update_ROTATING_CAMERA()
{
  Camera* camera = &*this->scene->getCamera();
  std::set<int> input = active_input->getInput();

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

void SceneEditor::update_MOVING_MODEL()
{
  Camera* camera = &*this->scene->getCamera();
  std::set<int> input = active_input->getInput();

  if( isSubset<int>( std::set<int>{ GLFW_MOUSE_BUTTON_1 }, input ) )
  {
    // select model
    this->moveSelectedModel();
  }
  else
  {
    resource_manager->getModel( "SceneEditor_arrow_x" )
      ->setTexture( resource_manager->getTexture( "red" ) );
    resource_manager->getModel( "SceneEditor_arrow_y" )
      ->setTexture( resource_manager->getTexture( "blue" ) );
    resource_manager->getModel( "SceneEditor_arrow_z" )
      ->setTexture( resource_manager->getTexture( "green" ) );
    this->state = MODEL_SELECTED;
  }
}

void SceneEditor::update()
{
  if( this->state == NO_SELECTION || this->state == MODEL_SELECTED )
    update_NO_SELECTION__MODEL_SELECTED();
  else if( this->state == ROTATING_CAMERA )
    update_ROTATING_CAMERA();
  else if( this->state == MOVING_MODEL )
    update_MOVING_MODEL();
}
