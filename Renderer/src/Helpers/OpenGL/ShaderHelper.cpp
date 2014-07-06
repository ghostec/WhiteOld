#include "Renderer/Helpers/OpenGL/ShaderHelper.h"

namespace ShaderHelper
{
  void setLight( Shader *shader, Light* light )
  {
    WMath::vec3 pos = light->getPosition( );
    float intensities[3] = { 1, 1, 1 };
    shader->setUniform( "lights[0].position", pos.vec );
    shader->setUniform( "lights[0].intensities", intensities );
    shader->setUniform( "lights[0].attenuation", 0.2f );
    shader->setUniform( "lights[0].ambientCoefficient", 0.005f );
  }

  void setCamera(Shader* shader, Camera* camera)
  {
	shader->setUniform( "camera.view",
      camera->getView(), GL_FALSE );
    shader->setUniform( "camera.proj",
      camera->getProj(), GL_FALSE );
  }
  void setModelData( Shader* shader, ModelData* model_data )
  {
    for( auto it = model_data->getFloatMap()->begin();
      it != model_data->getFloatMap()->end(); it++ )
    {
      shader->setUniform( it->first, it->second );
    }

    for( auto it = model_data->getMat4Map()->begin();
      it != model_data->getMat4Map()->end(); it++ )
    {
      shader->setUniform( it->first, &it->second, GL_FALSE );
    }
  }
}
