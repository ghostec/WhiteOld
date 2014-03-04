#ifndef __WHITE_MESH__
#define __WHITE_MESH__

#include "Renderer/Model.h"

class Mesh
{
  private:
    Model* model;
  public:
    Mesh( Model* model );
    void draw();
};

#endif
