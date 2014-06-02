#ifndef __RENDERER_HELPERS_OPENGL_SHADERHELPER__
#define __RENDERER_HELPERS_OPENGL_SHADERHELPER__

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Shader.h"
#include "Renderer/Light.h"
#include "Renderer/Camera.h"

namespace ShaderHelper
{
  void setLight( std::shared_ptr<Shader> shader, std::shared_ptr<Light> light );
  void setCamera( std::shared_ptr<Shader> shader, std::shared_ptr<Camera> camera );
}

#endif
