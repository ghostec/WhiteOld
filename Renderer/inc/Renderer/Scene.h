#ifndef __WHITE_SCENE__
#define __WHITE_SCENE__

#include <iostream>
#include <vector>
#include "Renderer/Model.h"

class Scene
{
  private:
    std::vector<Model*> models;
    Camera* camera;
    WMath::mat4 view, proj;
  public:
    Scene();
    void draw();
    void addModel( Model* model );
    void setCamera( Camera* camera );
};

#endif
