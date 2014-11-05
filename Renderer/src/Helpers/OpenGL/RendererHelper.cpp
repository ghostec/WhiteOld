#include "Renderer/Helpers/OpenGL/RendererHelper.h"

namespace RendererHelper
{
  void drawSGNode( std::shared_ptr<SGNode> n,
     std::shared_ptr<Shader> custom_shader )
  {
    std::shared_ptr<Model> model = n->getModel();

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
    std::queue< std::shared_ptr<SGNode> > bfs_q;
    std::vector< std::shared_ptr<SGNode> > bfs_v;

    bfs_q.push( scene_graph->getRootSGNode() );
    bfs_v.push_back( scene_graph->getRootSGNode() );

    while( !bfs_q.empty() )
    {
      std::shared_ptr<SGNode> n = bfs_q.front(); bfs_q.pop();
      std::shared_ptr<Model> model = n->getModel();

      if( n->isWorldTransformDirty() )
      {
        SGNodeWorldTransform w = n->getWorldTransform();
        SGNodePropagation pr = n->getPropagation();

        pr.t_node.position = pr.t_node.position + w.data.position;
        pr.t_node.scale = w.data.scale;
        pr.t_node.rotate = pr.t_node.rotate * w.data.rotate;

        WMath::mat4 t = WMath::scaleM( pr.t_node.scale )
          * WMath::rotateM( pr.t_node.rotate )
          * WMath::translateM( pr.t_node.position );
        n->setWorldTransform( t );

        for( auto c : n->getChildren() ) c->setPropagation( pr );

        n->setWorldTransformDirty( false );
      }

      if( model ) drawSGNode( n );

      for( auto c : n->getChildren( ) )
      {
        if( std::find( bfs_v.begin(), bfs_v.end(), c ) == bfs_v.end() )
        {
          bfs_q.push( c ); bfs_v.push_back( c );
        }
      }
    }
  }
}
