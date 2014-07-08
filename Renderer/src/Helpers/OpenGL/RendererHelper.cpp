#include "Renderer/Helpers/OpenGL/RendererHelper.h"

namespace RendererHelper
{
  void drawModel( std::shared_ptr<Model> model, GLuint frame_buffer )
  {
    model->update();
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
  }
}
