#ifndef __WHITE_SCENE__
#define __WHITE_SCENE__

#include <iostream>
#include <vector>
#include "Renderer/Mesh.h"

class Scene
{
  private:
    std::vector<Mesh*> meshes;
  public:
    void draw();
    void addMesh( Mesh* mesh );
};

#endif
