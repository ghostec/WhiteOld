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
#include "WMath/WMath.h"

typedef enum
{
  NORMAL, ROTATING_CAMERA
} SceneEditorState;

class SceneEditor
{
  private:
    std::shared_ptr<Scene> scene;
    MousePicking mouse_picking;
    std::shared_ptr<Model> selected_model;
    std::shared_ptr<Shader> old_selected_model_shader;
    std::shared_ptr<Shader> shader;
    SceneEditorState state;
  public:
    SceneEditor( std::shared_ptr<Scene> scene );
    void initialize();
    void selectModel();
    void mouseScroll();
    void update();
    void setState( SceneEditorState state ) { this->state = state; }
    SceneEditorState getState() { return this->state; }
};

#endif
