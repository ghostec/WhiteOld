#include "Renderer/Helpers/OpenGL/RendererHelper.h"

namespace RendererHelper
{
  void updateViewport( Viewport* viewport )
  {
    // TODO: if viewport dirty or window dirty
    ContainableIterator<Viewport, Window> it( viewport, active_window );

    for( Viewport* v = it.begin(); v != nullptr; v = it.next() )
    {
      for( auto s : v->getScenes() )
      {
        SGNodeIterator it( &*s->getSceneGraph()->getRootSGNode() );
        for( SGNode* n = it.begin(); n; n = it.next() );
      }
    }
  }

  void drawSGNode( SGNode* n, Shader* custom_shader )
  {
    Model* model = &*n->getModel();
    if( !model ) return;

    Mesh* mesh = &*model->getMesh();

    Shader* shader;
    if( custom_shader != nullptr )
    {
      ShaderHelper::setMesh( custom_shader, &*mesh );
      shader = custom_shader;
    }
    else shader = &*model->getShader();

    ShaderHelper::setModelData( shader, &*model->getModelData() );

    WMath::mat4 world_transform = n->getWorldTransformM();

    if( model->getModelType() == MODEL_2D )
    {
      glDisable( GL_DEPTH_TEST );
    }
    else
    {
      glEnable( GL_DEPTH_TEST );
    }

    model->use();
    shader->setUniform( "Model", &world_transform, GL_TRUE );
    shader->use();

    if( mesh->getIndexingType() == MESH_NOT_INDEXED )
      glDrawArrays( GL_TRIANGLES, 0, mesh->getVerticesCount() );
    else if( mesh->getIndexingType() == MESH_INDEXED )
    {
      
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh->getEBO() );
      glEnable( GL_PRIMITIVE_RESTART );
      glPrimitiveRestartIndex( 512*512 );
      glDrawElements( GL_TRIANGLE_STRIP, 523775, GL_UNSIGNED_INT, 0 );
      glDisable( GL_PRIMITIVE_RESTART );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
      
    }

    shader->unuse();
    model->unuse();

    if( custom_shader != nullptr )
    {
      // fixing Shader's layout on Mesh's VAO
      ShaderHelper::setMesh( &*model->getShader(), &*mesh );
    }
  }

  void drawSceneGraph( SceneGraph* scene_graph )
  {
    SGNodeIterator it( &*scene_graph->getRootSGNode() );
    for( SGNode* n = it.begin(); n; n = it.next() ) drawSGNode( n );
  }
}
