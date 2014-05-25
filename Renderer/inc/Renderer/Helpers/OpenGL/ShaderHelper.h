#ifndef __RENDERER_HELPERS_OPENGL_SHADERHELPER__
#define __RENDERER_HELPERS_OPENGL_SHADERHELPER__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Shader.h"
#include "Renderer/Light.h"
#include "Renderer/Camera.h"

namespace ShaderHelper
{
  void setLight( Shader* shader, Light* light );
  void setCamera( Shader* shader, Camera* camera );
}

#endif
