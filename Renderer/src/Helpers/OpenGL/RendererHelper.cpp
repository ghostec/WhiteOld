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
      * WMath::translateM( sg_node->getTranslate() );
    model->setTransform( &t );
    drawModel( model );
  }
}
