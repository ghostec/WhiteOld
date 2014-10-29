#include "Renderer/Helpers/OpenGL/RendererHelper.h"

namespace RendererHelper
{
  void drawModel( std::shared_ptr<Model> model, GLuint frame_buffer )
  {
    model->use();
    std::shared_ptr<Mesh> mesh = model->getMesh();
    std::shared_ptr<Shader> shader = model->getShader();

    glBindVertexArray( mesh->getVAO() );
    shader->use();

    if( model->getModelType( ) == MODEL_2D )
    {
      glDisable( GL_DEPTH_TEST );
    }
    else
    {
      glEnable( GL_DEPTH_TEST );
    }

    glDrawArrays( GL_TRIANGLES, 0, mesh->getVerticesCount() );

    shader->unuse();
    glBindVertexArray( 0 );

    model->unuse();
  }

  void drawSGNode( std::shared_ptr<SGNode> sg_node )
  {
    std::shared_ptr<Model> model = sg_node->getModel();
    WMath::mat4 t = WMath::scaleM( sg_node->getScale() )
      * WMath::rotateM( sg_node->getRotate() )
      * WMath::translateM( sg_node->getPosition() );
    model->setTransform( &t );
    drawModel( model );
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

      p_n.position = p_n.position + n->getPosition();
      p_n.scale = n->getScale();
      p_n.rotate = p_n.rotate * n->getRotate();

      WMath::vec3 pivot = n->getPivot();

      if( model )
      {
        WMath::mat4 t = WMath::scaleM( p_n.scale )
          * WMath::translateM( pivot ) * WMath::rotateM( p_n.rotate ) * WMath::translateM( -pivot )
          * WMath::translateM( p_n.position );
        model->setTransform( &t );
        drawModel( model );
      }

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
