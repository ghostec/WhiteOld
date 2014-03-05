#include "Renderer/Scene.h"

void Scene::draw()
{
  int vector_models_size = this->models.size();
  for( int i = 0; i < vector_models_size; i++ )
  {
    this->models.at(i)->draw();
  }
}

void Scene::addModel( Model* model )
{
  this->models.push_back( model );
}
