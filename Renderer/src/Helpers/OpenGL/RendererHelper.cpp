#include "Renderer/Helpers/OpenGL/RendererHelper.h"

namespace RendererHelper
{
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

    WMath::mat4 world_transform = n->getWorldTransformM();

    model->use();
    shader->setUniform( "Model", &world_transform, GL_TRUE );
    shader->use();
    glDrawArrays( GL_TRIANGLES, 0, mesh->getVerticesCount() );
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
