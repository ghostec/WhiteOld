#ifndef __WHITE_SHADERFACTORY__
#define __WHITE_SHADERFACTORY__

#include <iostream>
#include "Renderer/Shader.h"
#include "Renderer/ShaderGLSL.h"

class ShaderFactory
{
  private:
  public:
    virtual Shader* createShader() = 0;
};

class ShaderFactoryGLSL : public ShaderFactory
{
  private:
  public:
    Shader* createShader();
};

#endif
