#include "Renderer/SceneEditor.h"

SceneEditor::SceneEditor( std::shared_ptr<Scene> scene,
  std::shared_ptr<ResourceManager> resource_manager )
{
  this->shader.reset( new Shader( "wireframe" ) );
  this->scene = scene;
  this->selected_sg_node = nullptr;
  std::vector<Scene*> scenes = { &*scene };
  // this->mouse_picking.setScenes( scenes );
  this->resource_manager = resource_manager;
  XMLHelper::importAssets( "assets_SceneEditor", resource_manager );

  std::shared_ptr<Model> model_arrow_x = resource_manager->getModel( "SceneEditor_arrow_x" );
  std::shared_ptr<SGNode> node_arrow_x( new SGNode( "arrow_x", model_arrow_x ) );

  std::shared_ptr<Model> model_arrow_y = resource_manager->getModel( "SceneEditor_arrow_y" );
  std::shared_ptr<SGNode> node_arrow_y( new SGNode( "arrow_y", model_arrow_y ) );

  std::shared_ptr<Model> model_arrow_z = resource_manager->getModel( "SceneEditor_arrow_z" );
  std::shared_ptr<SGNode> node_arrow_z( new SGNode( "arrow_z", model_arrow_z ) );

  std::shared_ptr<SceneGraph> scene_graph = scene->getSceneGraph();
  scene_graph->addSGNode( node_arrow_x );
  scene_graph->addSGNode( node_arrow_y );
  scene_graph->addSGNode( node_arrow_z );

//  active_window->registerObserver( "RESIZE",
//    std::bind( &MousePicking::reset, &mouse_picking ), "MousePicking" );

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
  SGNode* sg_node = &*scene_editor->getSelectedSGNode();
  Model* model = &*sg_node->getModel();

  WMath::vec3 model_dimensions = model->getDimensions();

  std::shared_ptr<SceneGraph> scene_graph =
    scene_editor->getScene()->getSceneGraph();

  std::shared_ptr<Model> model_arrow_x = resource_manager->getModel( "SceneEditor_arrow_x" );
  std::shared_ptr<Model> model_arrow_y = resource_manager->getModel( "SceneEditor_arrow_y" );
  std::shared_ptr<Model> model_arrow_z = resource_manager->getModel( "SceneEditor_arrow_z" );

  std::shared_ptr<SGNode> node_arrow_x = scene_graph->findSGNode( "arrow_x" );
  std::shared_ptr<SGNode> node_arrow_y = scene_graph->findSGNode( "arrow_y" );
  std::shared_ptr<SGNode> node_arrow_z = scene_graph->findSGNode( "arrow_z" );

  float dx = 0.5f * ( model_dimensions[0] + model_arrow_x->getDimensions()[0] );
  node_arrow_x->setTranslate( sg_node->getTranslate() + WMath::vec3( dx, 0, 0 ) );
  //WMath::rotate_z( arrow_x->getRotateM(), -90.0f );
  float dy = 0.5f * ( model_dimensions[1] + model_arrow_y->getDimensions()[1] );
  node_arrow_y->setTranslate( sg_node->getTranslate() + WMath::vec3( 0, dy, 0 ) );
  float dz = 0.5f * ( model_dimensions[2] + model_arrow_z->getDimensions()[2] );
  node_arrow_z->setTranslate( sg_node->getTranslate() + WMath::vec3( 0, 0, dz ) );
  //WMath::rotate_x( arrow_z->getRotateM(), 90.0f );
}

void hideMoveArrows( std::shared_ptr<Scene> scene,
  std::shared_ptr<ResourceManager> resource_manager )
{

}

void showMoveArrows( SceneEditor* scene_editor,
  ResourceManager* resource_manager )
{
  updateMoveArrows( scene_editor, resource_manager );
}

void SceneEditor::moveSelectedSGNode( SceneEditorAxis direction )
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

    this->selected_sg_node->setTranslate( this->selected_sg_node->getTranslate() + dT );
    updateMoveArrows( this, &*this->resource_manager );
    last_cursor_pos = cursor_pos;
  }
}

void SceneEditor::selectSGNode( std::shared_ptr<SGNode> sg_node )
{
  if( this->selected_sg_node )
  {
    this->selected_sg_node->setModel( this->old_selected_model );
    hideMoveArrows( this->scene, this->resource_manager );
    this->state = NO_SELECTION;
  }
  if( sg_node )
  {
    this->old_selected_model = sg_node->getModel();
    this->selected_sg_node = sg_node;
    std::shared_ptr<Model> modified_model( new Model( old_selected_model->getMesh() ) );
    modified_model->setShader( resource_manager->getShader("wireframe") );
    modified_model->setTexture( old_selected_model->getTexture() );
    this->selected_sg_node->setModel( modified_model );
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
  static std::shared_ptr<SGNode> sg_node_hovered = nullptr;
  static std::shared_ptr<Texture> texture_hovered = nullptr;

  if( sg_node_hovered )
  {
    sg_node_hovered->getModel()->setTexture( texture_hovered );
    sg_node_hovered = nullptr; texture_hovered = nullptr;
  }

  std::shared_ptr<SGNode> sg_node; //= mouse_picking.pick();

  /*
  if( sg_node == this->scene->getSceneGraph()->getNode( "arrow_x" ) || 
    sg_node == this->scene->getSceneGraph()->getNode( "arrow_y" ) ||
    sg_node == this->scene->getSceneGraph()->getNode( "arrow_z" ) )
  {
    sg_node_hovered = sg_node;
    texture_hovered = sg_node->getModel()->getTexture();
    sg_node->getModel()->setTexture( resource_manager->getTexture( "yellow" ) );
  }
  */

  if( active_input->hasInput( std::set<int>{ GLFW_KEY_UP }, HOLD ) )
  {
    WMath::translate( camera->getView(), WMath::vec3( 0, -0.04, 0 ) );
  }
  else if( active_input->hasInput( std::set<int>{ GLFW_KEY_DOWN }, HOLD ) )
  {
    WMath::translate( camera->getView(), WMath::vec3( 0, 0.04, 0 ) );
  }
  else if( active_input->hasInput( std::set<int>{ GLFW_KEY_LEFT }, HOLD ) )
  {
    WMath::translate( camera->getView(), WMath::vec3( 0.04, 0, 0 ) );
  }
  else if( active_input->hasInput( std::set<int>{ GLFW_KEY_RIGHT }, HOLD ) )
  {
    WMath::translate( camera->getView(), WMath::vec3( -0.04, 0, 0 ) );
  }
  else if( active_input->hasInput( std::set<int>{ GLFW_KEY_LEFT_ALT, GLFW_MOUSE_BUTTON_1 }, HOLD ) )
  {
    rotateCamera( camera, this );
  }
  else if( active_input->hasInput( std::set<int>{ GLFW_MOUSE_BUTTON_1 }, HOLD ) )
  {
    this->selectSGNode( sg_node );
  }
}

void SceneEditor::update_ROTATING_CAMERA()
{
  Camera* camera = &*this->scene->getCamera();

  if( active_input->hasInput( std::set<int>{ GLFW_KEY_LEFT_ALT, GLFW_MOUSE_BUTTON_1 }, HOLD ) )
  {
    rotateCamera( camera, this );
  }
  else
  {
    if( this->selected_sg_node ) this->state = MODEL_SELECTED;
    else this->state = NO_SELECTION;
  }
}

void SceneEditor::update_MOVING_MODEL()
{
  Camera* camera = &*this->scene->getCamera();

  if( active_input->hasInput( std::set<int>{ GLFW_MOUSE_BUTTON_1 }, HOLD ) )
  {
    // select model
    this->moveSelectedSGNode();
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
