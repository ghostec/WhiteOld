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
    const std::shared_ptr<Model> model = sg_node->getModel();
    WMath::mat4 t = WMath::scaleM( sg_node->getScale() )
      * WMath::rotateM( sg_node->getRotate() )
      * WMath::translateM( sg_node->getTranslate() );
    model->setTransform( &t );
    drawModel( model );
  }

  void drawPropagatedSGNode( PropagatedSGNode propagated_node )
  {
    const std::shared_ptr<SGNode> sg_node = propagated_node.first;
    const PropagatedSGNodeData data = propagated_node.second;
    const std::shared_ptr<Model> model = sg_node->getModel();
    std::queue<PropagatedSGNode> q;
    std::vector< std::shared_ptr<SGNode> > v;

    q.push( propagated_node );
    v.push_back( propagated_node.first );

    while( !q.empty() )
    {
      PropagatedSGNode pn = q.front(); q.pop();
      std::shared_ptr<SGNode> n = pn.first;
      PropagatedSGNodeData pnd = pn.second;

      pnd.translate = pnd.translate + n->getTranslate();
      // SCALE
      // ROTATE

      if( n->getName() == "plane" )
      {
        pnd.translate = WMath::vec3(0 );
        pnd.scale = WMath::vec3(20);
      }

      const std::shared_ptr<Model> model = n->getModel( );
      if( model )
      {
        WMath::mat4 t = WMath::scaleM( pnd.scale )
          * WMath::rotateM( pnd.rotate )
          * WMath::translateM( pnd.translate );
        model->setTransform( &t );
        drawModel( model );
      }

      for( std::shared_ptr<SGNode> c : pn.first->getChildren() )
      {
        if( std::find( v.begin(), v.end(), c ) == v.end() )
        {
          v.push_back(c);
          PropagatedSGNode pcn = { c, pnd };
          q.push( pcn );
        }
      }
    }
  }
}
