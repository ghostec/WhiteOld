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
    this->selected_model_instance->getShaders()->pop_back();

  int id = this->mouse_picking->getIdForPosition();
  this->selected_model_instance = this->scene->getModelInstanceWithId( id );
  this->selected_model_instance->addShader( this->shader );
  this->scene->updateCamera();
}