#ifndef __RENDERER_SCENEEDITOR__
#define __RENDERER_SCENEEDITOR__

#include <vector>
#include "Renderer/Scene.h"
#include "Renderer/ModelInstance.h"
#include "Renderer/Shader.h"
#include "Renderer/MousePicking.h"

typedef struct Movable_
{
  bool ARROW_UP = false;
  bool ARROW_DOWN = false;
} Movable;

class SceneEditor
{
  private:
    std::shared_ptr<Scene> scene;
    std::shared_ptr<MousePicking> mouse_picking;
    std::shared_ptr<ModelInstance> selected_model_instance;
    std::shared_ptr<Shader> shader;
  public:
    Movable moves;
    SceneEditor( std::shared_ptr<Scene> scene, std::shared_ptr<MousePicking> mouse_picking, std::shared_ptr<Shader> shader );
    void selectModelInstance();
    void move();
};

#endif
