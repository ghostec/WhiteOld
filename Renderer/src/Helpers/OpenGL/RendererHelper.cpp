#include "Renderer/Helpers/OpenGL/RendererHelper.h"

namespace RendererHelper
{
  void drawPropagatedSGNode( PropagatedSGNode p_n,
     std::shared_ptr<Shader> custom_shader )
  {
    std::shared_ptr<Model> model = p_n.sg_node->getModel();

    WMath::mat4 world_transform;
    if( p_n.sg_node->isWorldTransformDirty() )
    {
      world_transform = WMath::scaleM( p_n.scale )
        * WMath::rotateM( p_n.rotate )
        * WMath::translateM( p_n.position );
      p_n.sg_node->setWorldTransform( world_transform );
    }
    else world_transform = p_n.sg_node->getWorldTransformM();

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
    std::queue<PropagatedSGNode> bfs_q;
    std::vector< std::shared_ptr<SGNode> > bfs_v;

    PropagatedSGNode p_sg_node;
    p_sg_node.sg_node = scene_graph->getRootSGNode();

    bfs_q.push( p_sg_node );
    bfs_v.push_back( scene_graph->getRootSGNode() );

    while( !bfs_q.empty() )
    {
      PropagatedSGNode p_n = bfs_q.front( ); bfs_q.pop( );
      std::shared_ptr<SGNode> n = p_n.sg_node;
      std::shared_ptr<Model> model = n->getModel();

      SGNodeWorldTransform w = n->getWorldTransform();

      p_n.position = p_n.position + w.position;
      p_n.scale = w.scale;
      p_n.rotate = p_n.rotate * w.rotate;

      if( model ) drawPropagatedSGNode( p_n );

      for( auto c : n->getChildren( ) )
      {
        if( std::find( bfs_v.begin(), bfs_v.end(), c ) == bfs_v.end() )
        {
          p_n.sg_node = c;
          bfs_q.push( p_n ); bfs_v.push_back( c );
        }
      }
    }
  }
}
