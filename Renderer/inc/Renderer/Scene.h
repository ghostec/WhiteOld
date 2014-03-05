#ifndef __WHITE_SCENE__
#define __WHITE_SCENE__

#include <iostream>
#include <vector>
#include "Renderer/Model.h"

class Scene
{
  private:
    std::vector<Model*> models;
  public:
    void draw();
    void addModel( Model* model );
};

#endif
