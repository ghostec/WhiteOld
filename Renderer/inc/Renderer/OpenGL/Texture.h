#ifndef __RENDERER_TEXTUREOPENGL__
#define __RENDERER_TEXTUREOPENGL__

#include <memory>
#include <string>
#include <GL/glew.h>
#include "SOIL/SOIL.h"
#include "Renderer/Shader.h"

class Texture
{
  private:
    GLuint texture;
  public:
    Texture( std::string name );
    void use( std::shared_ptr<Shader> shader );
    void unuse();
};

#endif
