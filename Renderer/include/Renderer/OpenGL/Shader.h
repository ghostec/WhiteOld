#ifndef __RENDERER_OPENGLSHADER__
#define __RENDERER_OPENGLSHADER__

#include <string>
#include "Renderer/Light.h"
#include "Renderer/Camera.h"
#include "Renderer/Helpers/MeshHelper.h"
#include "WMath/WMath.h"

class Shader
{
  private:
    std::string name;
  public:
    Shader( std::string name );
    GLuint shader;
    void use();
    void unuse();
    void setVertexAttribute(  std::string name, int count, int stride,
                              int offset );
    void setUniform( std::string name, const float value );
    void setUniform( std::string name, const float value[ 3 ] );
    void setUniform( std::string name, WMath::vec4 value );
    void setUniform( std::string name, WMath::mat4* value, bool transpose );
    // getters
    const std::string getName() { return this->name; };
};

#endif
