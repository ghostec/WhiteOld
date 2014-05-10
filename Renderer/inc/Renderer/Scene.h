#ifndef __WHITE_SCENE__
#define __WHITE_SCENE__

#include <iostream>
#include <vector>
#include "Renderer/Model.h"

typedef struct _SceneProperties
{
  WMath::mat4 view, proj;
} SceneProperties;

class Scene
{
  private:
    std::vector<Model*> models;
    Camera* camera;
    SceneProperties scene_properties;
  public:
    void draw();
    void addModel( Model* model );
    void setCamera( Camera* camera );
};

#endif
