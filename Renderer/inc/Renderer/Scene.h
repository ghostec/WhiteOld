#ifndef __WHITE_SCENE__
#define __WHITE_SCENE__

#include <iostream>
#include <vector>
#include "Renderer/ModelInstance.h"
#include "Renderer/Light.h"

class Scene
{
  private:
    std::vector<ModelInstance*> models;
    std::vector<Light*> lights;
    Camera* camera;
  public:
    void draw();
    void addModel( ModelInstance* model );
    void addLight( Light* light );
    void updateLights();
    void setCamera( Camera* camera );
    void updateCamera();
};

#endif
