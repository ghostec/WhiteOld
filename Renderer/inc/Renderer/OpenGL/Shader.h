#ifndef __WHITE_OPENGLSHADER__
#define __WHITE_OPENGLSHADER__

#include "Renderer/Light.h"
#include "Renderer/Camera.h"
#include "Renderer/OpenGL/Shader.h"
#include "Renderer/Helpers/Model.h"

class Shader
{
  private:
    
  public:
    Shader();
    GLuint shader;
    void before_draw();
    void after_draw();
    void setVertexAttribute(  std::string name, int count, int stride,
                              int offset );
    void setUniform1f( std::string name, GLfloat v0 );
    void setUniform3f( std::string name,
                        GLfloat v0,
                        GLfloat v1,
                        GLfloat v2 );
    void setUniformMatrix4fv( std::string name,
                              const GLfloat *value,
                              GLboolean transpose);
    void setLight( Light* light );
    void setCamera( Camera* camera );
};

#endif
