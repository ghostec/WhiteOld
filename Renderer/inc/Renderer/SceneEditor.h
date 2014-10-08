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
#include "Renderer/SGNode.h"
#include "Renderer/SceneGraph.h"
#include "WMath/WMath.h"

typedef struct _SceneEditorData
{
  std::shared_ptr<SGNode> arrow_x, arrow_y, arrow_z;
} SceneEditorData;

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
    std::shared_ptr<SGNode> selected_sg_node;
    std::shared_ptr<Model> old_selected_model;
    std::set< std::shared_ptr<SGNode> > locked_sg_nodes;
    std::shared_ptr<Shader> shader;
    SceneEditorState state;
    SceneEditorData data;
    // methods
    void showMoveArrows();
    void hideMoveArrows();
    void moveSelectedSGNode( SceneEditorAxis direction = SEA_NONE );
    void selectSGNode( std::shared_ptr<SGNode> sg_node );
    void mouseScroll();
    void update_NO_SELECTION__MODEL_SELECTED();
    void update_ROTATING_CAMERA();
    void update_MOVING_MODEL();
  public:
    //std::set< std::shared_ptr<SGNode> > cant_select;
    SceneEditor( std::shared_ptr<Scene> scene,
      std::shared_ptr<ResourceManager> resource_manager );
    void initialize();
    std::shared_ptr<SGNode> getSelectedSGNode() { return this->selected_sg_node; }
    void update();
    void setState( SceneEditorState state ) { this->state = state; }
    SceneEditorState getState() { return this->state; }
    std::shared_ptr<Scene> getScene() { return this->scene; }
};

#endif
