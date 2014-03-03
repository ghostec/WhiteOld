#include <Mesh.h>

Mesh::Mesh( Model* model )
{
  this->model = model;
}

void Mesh::draw()
{
  this->model->draw();
}
