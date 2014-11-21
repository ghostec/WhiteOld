#ifndef __RENDERER_HELPERS_OPENGL_SHADERHELPER__
#define __RENDERER_HELPERS_OPENGL_SHADERHELPER__

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Shader.h"
#include "Renderer/Light.h"
#include "Renderer/Camera.h"
#include "Renderer/Mesh.h"
#include "Renderer/Model.h"
#include "Renderer/Material.h"
#include "Renderer/ModelData.h"

namespace ShaderHelper
{
  void setLight( Shader* shader, Light* light );
  void setCamera( Shader* shader, Camera* camera );
  void setMesh( Shader* shader, Mesh* mesh );
  void setModelData( Shader* shader, ModelData* model_data );
  void setMaterial( Shader* shader, Material* material );
}

#endif
