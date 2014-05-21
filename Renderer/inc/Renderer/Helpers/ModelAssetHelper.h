#ifndef __RENDERER_MODELHELPER__
#define __RENDERER_MODELHELPER__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <regex>
#include <array>
#include <GL/glew.h>
#include "WMath/WMath.h"
#include "Helpers/Application.h"

namespace ModelAssetHelper
{
  void ImportOBJ( const char* filename, std::vector<WMath::vec3> &vertices,
                  std::vector<WMath::vec3>& uvs,
                  std::vector<WMath::vec3>& normals,
                  std::vector< std::array<GLushort, 3> > &elements );

  std::vector< WMath::vec3 >
    CalculateNormalsAveraged( std::vector<WMath::vec3>& vertices,
                              std::vector< std::array<GLushort, 3> >& elements );

  namespace OpenGL
  {

    GLuint CreateShader( GLenum shader_type, std::string file_path);

    GLuint CreateShaderProgram( GLuint vertex_shader, GLuint fragment_shader );

    GLuint CreateShaderProgram( std::string vertex_shader_file_path,
        std::string fragment_shader_file_path );

  }
}

#endif