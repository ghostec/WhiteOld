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
#include "ApplicationHelper.h"

namespace ModelHelper
{

  void ImportOBJ(
      std::string filePath,
      std::vector< WMath::vec3 >* vertices,
      std::vector< WMath::vec3 >* normals,
      std::vector< GLuint >* vertexIndices,
      std::vector< GLuint >* normalIndices,
      std::vector< GLuint >* uvIndices
      );

  namespace OpenGL
  {

    GLuint CreateShader( GLenum shader_type, std::string file_path);

    GLuint CreateShaderProgram( GLuint vertex_shader, GLuint fragment_shader );

    GLuint CreateShaderProgram( std::string vertex_shader_file_path,
        std::string fragment_shader_file_path );

  }
}

#endif
