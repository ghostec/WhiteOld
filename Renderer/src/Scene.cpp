#include <Scene.h>

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
