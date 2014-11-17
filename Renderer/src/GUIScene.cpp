#include "Renderer/GUIScene.h"

GUIScene::GUIScene( std::string name )
{
  this->name = name;
  this->scene_graph.reset( new SceneGraph() );
  this->scene.reset( new Scene( this->name ) );
  this->scene->setSceneGraph( this->scene_graph );
  this->rootGUIElement = nullptr;
}

void GUIScene::setRootGUIElement( std::shared_ptr<GUIElement> g )
{
  if( this->rootGUIElement != nullptr )
  {
    this->scene_graph->removeSGNode
      ( this->rootGUIElement->getSGNode()->getName() );
  }
  this->rootGUIElement = g;
  this->scene_graph->addSGNode( this->rootGUIElement->getSGNode() );
}

void GUIScene::update()
{
  ContainableIterator< GUIElement, Viewport >
    it( &*this->rootGUIElement, &*this->viewport );

  WMath::vec2 p_dimensions = this->viewport->getDimensions();

  for( GUIElement* g = it.begin(); g != nullptr; g = it.next() )
  {
    SGNode* sg_node = &*g->getSGNode();
    ContainableCachedData g_data = g->getContainableCachedData();

    WMath::vec3 scale
      ( g_data.dimensions[0] / p_dimensions[0],
        g_data.dimensions[1] / p_dimensions[1], 1.0f );

    WMath::vec3 position;
    position[0] = g_data.anchor[0] + g_data.dimensions[0] / 2.0f;
    position[1] = g_data.anchor[1] + g_data.dimensions[1] / 2.0f;

    position[0] = ( 2.0f * position[0] ) / p_dimensions[0] - 1.0f;
    position[1] = ( -2.0f * position[1] ) / p_dimensions[1] + 1.0f;

    SGNodeWorldTransform w;
    w.data.position = position;
    w.data.scale = scale;

    sg_node->setWorldTransform( w );
  }
}
