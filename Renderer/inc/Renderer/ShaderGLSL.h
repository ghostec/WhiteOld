#ifndef __WHITE_SHADERGLSL__
#define __WHITE_SHADERGLSL__

#include "Renderer/Shader.h"
#include "Renderer/ModelHelper.h"

class ShaderGLSL : public Shader
{
  private:
    GLuint shader;
  public:
    ShaderGLSL();
    void before_draw();
    void after_draw();
    void setVertexAttribute( std::string name, int count );
    void setUniformMatrix4fv( std::string name,
                              const GLfloat *value,
                              GLboolean transpose);
};

#endif
