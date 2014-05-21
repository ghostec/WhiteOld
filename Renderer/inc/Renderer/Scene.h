#ifndef __WHITE_SCENE__
#define __WHITE_SCENE__

#include <iostream>
#include <vector>
#include "Renderer/Model.h"
#include "Renderer/Light.h"

class Scene
{
  private:
    std::vector<Model*> models;
    std::vector<Light*> lights;
    Camera* camera;
  public:
    void draw();
    void addModel( Model* model );
    void addLight( Light* light );
    void updateLights();
    void setCamera( Camera* camera );
    void updateCamera();
};

#endif
