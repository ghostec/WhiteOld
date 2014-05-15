#ifndef __WHITE_MODELHELPER__
#define __WHITE_MODELHELPER__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <GL/glew.h>
#include "WMath/WMath.h"
#include "Helpers/Application.h"

namespace ModelHelper
{

  void ImportOBJ( const char* filename, std::vector<WMath::vec4> &vertices, std::vector<WMath::vec3> &normals, std::vector<GLushort> &elements );

  namespace OpenGL
  {

    GLuint CreateShader( GLenum shader_type, std::string file_path);

    GLuint CreateShaderProgram( GLuint vertex_shader, GLuint fragment_shader );

    GLuint CreateShaderProgram( std::string vertex_shader_file_path,
        std::string fragment_shader_file_path );

  }
}

#endif
