#include "Renderer/ShaderFactory.h"

Shader* ShaderFactoryGLSL::createShader()
{
  return new ShaderGLSL();
}
