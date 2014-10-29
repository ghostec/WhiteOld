#include "Renderer/GUIScene.h"

void GUIScene::update()
{
  ContainableIterator< GUIElement, Viewport >
    it( &*this->rootGUIElement, &*this->viewport );

  WMath::vec2 p_dimensions = this->viewport->getDimensions();

  for( GUIElement* g = it.begin(); g != nullptr; g = it.next() )
  {
    SGNode* sg_node = &*g->getSGNode();
    ContainableCachedData g_data = g->getContainableCachedData();

    WMath::vec2 scale
      ( g_data.dimensions[0] / p_dimensions[0],
        g_data.dimensions[1] / p_dimensions[1] );

    sg_node->setPosition
      ( WMath::vec3( (2.0f * (g_data.anchor[0] + g_data.dimensions[0] / 2.0f)) / p_dimensions[0] - 1.0f,
                     (-2.0f * (g_data.anchor[1] + g_data.dimensions[1] / 2.0f)) / p_dimensions[1] + 1.0f,
                     0.0f ) );
    sg_node->setScale( WMath::vec3( scale[0], scale[1], 1.0 ) );
  }
}
