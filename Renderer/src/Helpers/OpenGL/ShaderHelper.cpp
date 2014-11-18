#include "Renderer/Helpers/OpenGL/ShaderHelper.h"

namespace ShaderHelper
{
  void setLight( Shader *shader, Light* light )
  {
    WMath::vec3 pos = light->getPosition();
    WMath::vec3 col = light->getColor();

    shader->setUniform( "lights[0].position", pos.vec );
    shader->setUniform( "lights[0].intensities", col.vec );
    shader->setUniform( "lights[0].attenuation", light->getAttenuation() );
    shader->setUniform( "lights[0].ambientCoefficient",
      light->getAmbientCoefficient() );
  }

  void setCamera( Shader* shader, Camera* camera )
  {
    shader->setUniform( "camera.view",
      camera->getView(), GL_TRUE );
    shader->setUniform( "camera.proj",
      camera->getProj(), GL_FALSE );
  }

  void setMesh( Shader* shader, Mesh* mesh )
  {
    glBindVertexArray( mesh->getVAO() );
    glBindBuffer( GL_ARRAY_BUFFER, mesh->getVBO() );

    MeshType mesh_type = mesh->getType();

    if( mesh_type == MESH_V3NT )
    {
      shader->setVertexAttribute( "vPosition", 3, 3 * sizeof( WMath::vec3 ),
          0 );
      shader->setVertexAttribute( "vUV", 3, 3 * sizeof( WMath::vec3 ),
          sizeof( WMath::vec3 ) );
      shader->setVertexAttribute( "vNormal", 3, 3 * sizeof( WMath::vec3 ),
          2 * sizeof( WMath::vec3 ) );
    }
    else if( mesh_type == MESH_V2T )
    {
      shader->setVertexAttribute( "vPosition", 2, sizeof( WMath::vec4 ),
          0 );
      shader->setVertexAttribute( "vUV", 2, sizeof( WMath::vec4 ),
          sizeof( WMath::vec2 ) );
    }
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
  }

  void setModelData( Shader* shader, ModelData* model_data )
  {
    for( auto& o : model_data->get< WMath::vec4 >() )
      shader->setUniform( o.first, o.second );
  }
}
