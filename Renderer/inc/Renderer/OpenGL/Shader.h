#ifndef __WHITE_OPENGLSHADER__
#define __WHITE_OPENGLSHADER__

#include "Renderer/OpenGL/Shader.h"
#include "Renderer/Helpers/Model.h"

class Shader
{
  private:
    GLuint shader;
  public:
    Shader();
    void before_draw();
    void after_draw();
    void setVertexAttribute( std::string name, int count );
    void setUniform3f( std::string name,
                        GLfloat v0,
                        GLfloat v1,
                        GLfloat v2 );
    void setUniformMatrix4fv( std::string name,
                              const GLfloat *value,
                              GLboolean transpose);
};

#endif
