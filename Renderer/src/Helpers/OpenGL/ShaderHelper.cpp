#include "Renderer/Helpers/OpenGL/ShaderHelper.h"

namespace ShaderHelper
{
  void setLight( std::shared_ptr<Shader> shader, std::shared_ptr<Light> light )
  {
    WMath::vec3 pos = light->getPosition( );
    shader->setUniform3f( "lights[0].position", pos[0], pos[1], pos[2] );
    shader->setUniform3f( "lights[0].intensities", 1.0f, 1.0f, 1.0f );
    shader->setUniform1f( "lights[0].attenuation", 0.2f );
    shader->setUniform1f( "lights[0].ambientCoefficient", 0.005f );
  }

  void setCamera( std::shared_ptr<Shader> shader, std::shared_ptr<Camera> camera )
  {
    shader->setUniformMatrix4fv( "camera.view",
      WMath::value_ptr( camera->getView( ) ), GL_FALSE );
    shader->setUniformMatrix4fv( "camera.proj",
      WMath::value_ptr( camera->getProj( ) ), GL_FALSE );
  }
}
