#include "Renderer/Scene.h"

Scene::Scene( std::string name )
{
  this->name = name;
  this->camera.reset( new Camera() );
  this->camera->setProjectionType( CAMERA_PROJECTION_ORTHOGRAPHIC );
}

void Scene::update()
{
  std::vector< std::shared_ptr<Model> > models;
  std::vector< std::shared_ptr<Shader> > shaders;
  std::queue< std::shared_ptr<SGNode> > bfs_q;
  std::vector< std::shared_ptr<SGNode> > bfs_v;

  bfs_q.push( this->scene_graph->getRootSGNode() );
  bfs_v.push_back( this->scene_graph->getRootSGNode() );

  while( !bfs_q.empty() )
  {
    std::shared_ptr<SGNode> n = bfs_q.front(); bfs_q.pop();
    std::shared_ptr<Model> model = n->getModel();

    if( model &&
      ( std::find( models.begin(), models.end(), model ) == models.end() ) )
    {
      std::shared_ptr<Shader> shader = model->getShader();

      if( std::find( shaders.begin(), shaders.end(), shader ) == shaders.end() )
      {
        if( this->lights.size() > 0 )
        ShaderHelper::setLight( &*shader, &this->lights[0] );
        ShaderHelper::setCamera( &*shader, &*this->camera );
        shaders.push_back( shader );
      }

      models.push_back( model );
    }

    for( auto c : n->getChildren() )
    {
      if( std::find( bfs_v.begin(), bfs_v.end(), c ) == bfs_v.end() )
      {
        bfs_q.push( c ); bfs_v.push_back( c );
      }
    }
  }
}

void Scene::addLight( Light light )
{
  this->lights.push_back( light );
}

void Scene::updateLightsForShader( std::shared_ptr<Shader> shader )
{
  ShaderHelper::setLight( &*shader, &this->lights[0] );
}

void Scene::updateCameraForShader( std::shared_ptr<Shader> shader )
{
  ShaderHelper::setCamera( &*shader, &*this->camera );
}

void Scene::setCamera( std::shared_ptr<Camera> camera )
{
  this->camera = camera;
  std::string text = this->name + "_camera";
}

void Scene::setSceneGraph( std::shared_ptr<SceneGraph> scene_graph )
{
  this->scene_graph = scene_graph;
}
