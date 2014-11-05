#include "Renderer/Helpers/OpenGL/RendererHelper.h"

namespace RendererHelper
{
  void drawSGNode( SGNode* n,
     std::shared_ptr<Shader> custom_shader )
  {
    std::shared_ptr<Model> model = n->getModel();
    if( !model ) return;

    WMath::mat4 world_transform = n->getWorldTransformM();

    model->use();

    std::shared_ptr<Mesh> mesh = model->getMesh();

    std::shared_ptr<Shader> shader;
    if( custom_shader != nullptr ) shader = custom_shader;
    else shader = model->getShader();

    shader->setUniform( "Model", &world_transform, GL_TRUE );

    glBindVertexArray( mesh->getVAO() );
    shader->use();

    if( model->getModelType() == MODEL_2D ) glDisable( GL_DEPTH_TEST );
    else glEnable( GL_DEPTH_TEST );

    glDrawArrays( GL_TRIANGLES, 0, mesh->getVerticesCount() );

    shader->unuse();
    glBindVertexArray( 0 );

    model->unuse();
  }

  void drawSceneGraph( std::shared_ptr<SceneGraph> scene_graph )
  {
    SGNodeIterator it( &*scene_graph->getRootSGNode() );
    for( SGNode* n = it.begin(); n; n = it.next() ) drawSGNode( n );
  }
}
