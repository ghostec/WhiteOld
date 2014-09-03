#ifndef __RENDERER_SCENEEDITOR__
#define __RENDERER_SCENEEDITOR__

#include <vector>
#include <set>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Scene.h"
#include "Renderer/Model.h"
#include "Renderer/Shader.h"
#include "Renderer/MousePicking.h"
#include "Renderer/Window.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/Helpers/XMLAssets.h"
#include "WMath/WMath.h"

typedef enum
{
  NO_SELECTION, MODEL_SELECTED, MOVING_MODEL, MOVING_CAMERA, ROTATING_CAMERA
} SceneEditorState;

typedef enum
{
  SEA_X, SEA_Y, SEA_Z, SEA_NONE
} SceneEditorAxis;

class SceneEditor
{
  private:
    std::shared_ptr<ResourceManager> resource_manager;
    std::shared_ptr<Scene> scene;
    MousePicking mouse_picking;
    std::shared_ptr<Model> selected_model;
    std::shared_ptr<Shader> old_selected_model_shader;
    std::shared_ptr<Shader> shader;
    std::set< std::shared_ptr<Model> > cant_select;
    SceneEditorState state;

    void moveSelectedModel( SceneEditorAxis direction = SEA_NONE );
    void selectModel( std::shared_ptr<Model> model );
    void mouseScroll();
    void update_NO_SELECTION__MODEL_SELECTED();
    void update_ROTATING_CAMERA();
    void update_MOVING_MODEL();
  public:
    SceneEditor( std::shared_ptr<Scene> scene,
      std::shared_ptr<ResourceManager> resource_manager );
    void initialize();
    std::shared_ptr<Model> getSelectedModel() { return this->selected_model; }
    void update();
    void setState( SceneEditorState state ) { this->state = state; }
    SceneEditorState getState() { return this->state; }
    std::shared_ptr<Scene> getScene() { return this->scene; }
};

#endif
