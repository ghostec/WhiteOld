#ifndef __RENDERER_SCENEEDITOR__
#define __RENDERER_SCENEEDITOR__

#include <vector>
#include "Renderer/Scene.h"
#include "Renderer/ModelInstance.h"
#include "Renderer/Shader.h"
#include "Renderer/MousePicking.h"

class SceneEditor
{
  private:
    Scene* scene;
    MousePicking* mouse_picking;
    ModelInstance* selected_model_instance;
    Shader* shader;
  public:
    SceneEditor( Scene* scene, MousePicking* mouse_picking, Shader& shader );
    void selectModelInstance();
};

#endif
