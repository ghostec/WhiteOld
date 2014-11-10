#ifndef __WHITE_RENDERER_OPENGL_TEXTURE__
#define __WHITE_RENDERER_OPENGL_TEXTURE__

#include <memory>
#include <string>
#include <GL/glew.h>
#include "SOIL/SOIL.h"
#include "Renderer/Shader.h"
#include "WMath/WMath.h"

class Texture
{
  private:
    GLuint texture;
  public:
    Texture( WMath::vec2 dimensions );
    Texture( std::string name );
    void use( std::shared_ptr<Shader> shader );
    void unuse();
};

#endif
