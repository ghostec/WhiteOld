#ifndef __RENDERER_SCENEEDITOR__
#define __RENDERER_SCENEEDITOR__

#include <vector>
#include "Renderer/Scene.h"
#include "Renderer/Model.h"
#include "Renderer/Shader.h"
#include "Renderer/MousePicking.h"
#include "Renderer/Window.h"

typedef struct Movable_
{
  bool ARROW_UP = false;
  bool ARROW_DOWN = false;
} Movable;

class SceneEditor
{
  private:
    std::shared_ptr<Scene> scene;
    MousePicking mouse_picking;
    std::shared_ptr<Model> selected_model;
    std::shared_ptr<Shader> old_selected_model_shader;
    std::shared_ptr<Shader> shader;
  public:
    Movable moves;
    SceneEditor( std::shared_ptr<Scene> scene );
    void initialize();
    void selectModel();
    void move();
};

#endif
