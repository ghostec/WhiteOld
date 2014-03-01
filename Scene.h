#ifndef __WHITE_SCENE__
#define __WHITE_SCENE__

#include <iostream>
#include <vector>
#include "Mesh.h"

class Scene
{
  private:
    std::vector<Mesh*> meshes;
  public:
    void draw();
    void addMesh( Mesh* mesh );
};

void Scene::draw()
{
  int vector_meshes_size = this->meshes.size();
  for( int i = 0; i < vector_meshes_size; i++ )
  {
    this->meshes.at(i)->draw();
  }
}

void Scene::addMesh( Mesh* mesh )
{
  this->meshes.push_back( mesh );
}

#endif
