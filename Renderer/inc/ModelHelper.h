#ifndef __WHITE_MODELHELPER__
#define __WHITE_MODELHELPER__

#include <iostream>
#include <string>
#include <GL/glew.h>
#include "../../ApplicationHelper.h"

namespace ModelHelper
{

  void ImportOBJ();

  namespace OpenGL
  {

    GLuint CreateShader( GLenum shader_type, std::string file_path);

    GLuint CreateShaderProgram( GLuint vertex_shader, GLuint fragment_shader );

    GLuint CreateShaderProgram( std::string vertex_shader_file_path,
                                std::string fragment_shader_file_path );

  }
}

#endif
