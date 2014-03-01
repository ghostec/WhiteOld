#ifndef __WHITE_MESH__
#define __WHITE_MESH__

#include "Model.h"

class Mesh
{
  private:
    Model* model;
  public:
    Mesh( Model* model );
    void draw();
};

Mesh::Mesh( Model* model )
{
  this->model = model;
}

void Mesh::draw()
{
  this->model->draw();
}

#endif
