#ifndef __RENDERER_OPENGLSHADER__
#define __RENDERER_OPENGLSHADER__

#include <string>
#include "Renderer/Light.h"
#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/Helpers/ModelAssetHelper.h"
#include "WMath/WMath.h"

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
    void setUniform( std::string name, const float value );
    void setUniform( std::string name, const float value[3] );
    void setUniform( std::string name, WMath::mat4* value, bool transpose );
    // getters
    DrawMode getDrawMode() { return this->draw_mode; };
    const std::string getName() { return this->name; };
};

#endif
