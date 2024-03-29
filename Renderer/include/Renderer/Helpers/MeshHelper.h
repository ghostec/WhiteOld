#ifndef __WHITE_RENDERER_MESHHELPER__
#define __WHITE_RENDERER_MESHHELPER__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <regex>
#include <array>
#include <memory>
#include <GL/glew.h>
#include "WMath/WMath.h"
#include "Helpers/Application.h"

namespace MeshHelper
{
  void indexedToNotIndexed( std::vector<WMath::vec3>& vertices,
    std::vector<WMath::vec3>& uvs,
    std::vector<WMath::vec3>& normals,
    std::vector< std::array<GLushort, 3> > &elements );

  void ImportOBJ( const char* filename, std::vector<WMath::vec3> &vertices,
                  std::vector<WMath::vec3>& uvs,
                  std::vector<WMath::vec3>& normals,
                  std::vector< std::array<GLushort, 3> > &elements );

  std::vector< WMath::vec3 >
    CalculateNormalsAveraged( std::vector<WMath::vec3>& vertices,
                              std::vector< std::array<GLushort, 3> >& elements );

  WMath::vec3 calculateDimensions( std::vector<WMath::vec3>& vertices );

  namespace OpenGL
  {

    GLuint CreateShader( GLenum shader_type, std::string file_path);

    GLuint CreateShaderProgram( GLuint vertex_shader, GLuint fragment_shader, GLuint geometry_shader );

    GLuint CreateShaderProgram( std::string vertex_shader_file_path,
      std::string fragment_shader_file_path,
      std::string geometry_shader_file_path = "" );

  }
}

#endif
