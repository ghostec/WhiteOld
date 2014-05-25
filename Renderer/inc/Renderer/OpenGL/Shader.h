#ifndef __RENDERER_OPENGLSHADER__
#define __RENDERER_OPENGLSHADER__

#include <string>
#include "Renderer/Light.h"
#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/Helpers/ModelAssetHelper.h"

class Shader
{
  private:
    DrawMode draw_mode;
    std::string name;
  public:
    Shader( std::string name );
    GLuint shader;
    void use();
    void unuse();
    void setDrawMode( DrawMode draw_mode );
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
    // getters
    DrawMode getDrawMode() { return this->draw_mode; };
    const std::string getName() { return this->name; };
};

#endif
