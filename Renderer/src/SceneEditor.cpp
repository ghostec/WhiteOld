#include "Renderer/SceneEditor.h"

SceneEditor::SceneEditor( std::shared_ptr<Scene> scene,
  std::shared_ptr<ResourceManager> resource_manager,
  std::shared_ptr<PhysicsManager> physics_manager )
{
  this->physics_manager = physics_manager;
  this->shader.reset( new Shader( "wireframe" ) );
  this->scene = scene;
  this->selected_sg_node = nullptr;
  this->resource_manager = resource_manager;
  XMLHelper::importAssets( "assets_SceneEditor", resource_manager );

  std::shared_ptr<Model> model_arrow_x = resource_manager->getModel( "SceneEditor_arrow_x" );
  this->data.arrow_x.reset( new SGNode( "arrow_x", model_arrow_x ) );

  std::shared_ptr<Model> model_arrow_y = resource_manager->getModel( "SceneEditor_arrow_y" );
  this->data.arrow_y.reset( new SGNode( "arrow_y", model_arrow_y ) );

  std::shared_ptr<Model> model_arrow_z = resource_manager->getModel( "SceneEditor_arrow_z" );
  this->data.arrow_z.reset( new SGNode( "arrow_z", model_arrow_z ) );

  this->locked_sg_nodes.insert( data.arrow_x );
  this->locked_sg_nodes.insert( data.arrow_y );
  this->locked_sg_nodes.insert( data.arrow_z );

  active_window->registerObserver( "RESIZE",
    std::bind( &MousePicking::reset, active_mouse_picking ), "MousePicking" );

  this->state = NO_SELECTION;
}

void SceneEditor::initialize()
{
  active_input->registerObserver
    ( "MOUSE_SCROLL", std::bind( &SceneEditor::mouseScroll, this ),
    "SceneEditor::selectModel" );
}

void SceneEditor::hideMoveArrows()
{
  std::shared_ptr<SGNode> n = this->getSelectedSGNode();
  n->removeChild( "arrow_x" );
  n->removeChild( "arrow_y" );
  n->removeChild( "arrow_z" );
}

void SceneEditor::showMoveArrows()
{
  std::shared_ptr<SGNode> n = this->getSelectedSGNode();
  n->addChild( this->data.arrow_x );
  n->addChild( this->data.arrow_y );
  n->addChild( this->data.arrow_z );

  std::shared_ptr<Model> model = n->getModel();
  WMath::vec3 model_dimensions = n->getDimensions();

  float dx = 0.5f * ( model_dimensions[0] +
    this->data.arrow_x->getDimensions()[0] );
  //this->data.arrow_x->setPosition( WMath::vec3( dx, 0, 0 ) );
  //this->data.arrow_x->setRotate( WMath::quaternion(0,0,1,180) );

  float dy = 0.5f * ( model_dimensions[1] +
    this->data.arrow_y->getDimensions()[1] );
  //this->data.arrow_y->setPosition( WMath::vec3( 0, dy, 0 ) );

  float dz = 0.5f * ( model_dimensions[2] +
    this->data.arrow_z->getDimensions()[0] );
  //this->data.arrow_z->setPosition( WMath::vec3( 0, 0, dz ) );
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

    //this->selected_sg_node->setPosition( this->selected_sg_node->getPosition() + dT );
    last_cursor_pos = cursor_pos;
  }
}

void SceneEditor::selectSGNode( std::shared_ptr<SGNode> sg_node )
{
  if( this->selected_sg_node )
  {
    this->selected_sg_node->setModel( this->old_selected_model );
    hideMoveArrows();
    this->state = NO_SELECTION;
  }
  if( sg_node )
  {
    this->old_selected_model = sg_node->getModel();
    this->selected_sg_node = sg_node;
    std::shared_ptr<Model> modified_model( new Model( old_selected_model->getName(), old_selected_model->getMesh() ) );
    modified_model->setShader( this->shader );
    modified_model->getMaterial()->setTexture( old_selected_model->getMaterial()->getTexture() );
    this->selected_sg_node->setModel( modified_model );
    showMoveArrows();
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
    sg_node_hovered->getModel()->getMaterial()->setTexture( texture_hovered );
    sg_node_hovered = nullptr; texture_hovered = nullptr;
  }

  std::shared_ptr<SGNode> sg_node = active_mouse_picking->pick();
  
  if( sg_node && ( sg_node->getName() == "arrow_x" 
    || sg_node->getName() == "arrow_y"
    || sg_node->getName() == "arrow_z" ) )
  {
    sg_node_hovered = sg_node;
    texture_hovered = sg_node->getModel()->getMaterial()->getTexture();
    sg_node->getModel()->getMaterial()->setTexture( resource_manager->getTexture( "yellow" ) );
  }

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
  else if( active_input->hasInput( std::set<int>{ GLFW_MOUSE_BUTTON_1 }, PRESS ) )
  {
    if( sg_node && ( sg_node->getName() == "arrow_x"
      || sg_node->getName() == "arrow_y"
      || sg_node->getName() == "arrow_z" ) )
    {
      if( sg_node->getName() == "arrow_x" ) moveSelectedSGNode( SEA_X );
      else if( sg_node->getName() == "arrow_y" ) moveSelectedSGNode( SEA_Y );
      else moveSelectedSGNode( SEA_Z );
    }
    else this->selectSGNode( sg_node );
  }
  else if( active_input->hasInput( std::set<int>{ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_C  }, PRESS ) )
  {
    this->clipboard_sg_node = selected_sg_node;
  }
  else if( active_input->hasInput( std::set<int>{ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_V  }, PRESS ) )
  {
    std::shared_ptr<SGNode> new_sg_node( new SGNode( "copy" + this->clipboard_sg_node->getName(), this->clipboard_sg_node->getModel() ) );
    //new_sg_node->setPosition( this->clipboard_sg_node->getPosition() );
    this->scene->getSceneGraph()->addSGNode( new_sg_node );

    std::shared_ptr<Body> body( new Body( new_sg_node ) );
    this->physics_manager->addBody( body );

    selectSGNode( new_sg_node );
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
      ->getMaterial()->setTexture( resource_manager->getTexture( "red" ) );
    resource_manager->getModel( "SceneEditor_arrow_y" )
      ->getMaterial()->setTexture( resource_manager->getTexture( "blue" ) );
    resource_manager->getModel( "SceneEditor_arrow_z" )
      ->getMaterial()->setTexture( resource_manager->getTexture( "green" ) );
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
