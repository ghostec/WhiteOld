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
    Scene* scene;
    MousePicking* mouse_picking;
    ModelInstance* selected_model_instance;
    Shader* shader;
  public:
    Movable moves;
    SceneEditor( Scene* scene, MousePicking* mouse_picking, Shader& shader );
    void selectModelInstance();
    void move();
};

#endif
