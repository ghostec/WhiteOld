#ifndef __RENDERER_MESHOPENGL__
#define __RENDERER_MESHOPENGL__

#include <iostream>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include "Renderer/Shader.h"
#include "Renderer/Helpers/ModelAssetHelper.h"
#include "WMath/WMath.h"
#include "WMath/transformations.h"
#include "Helpers/Application.h"

class Mesh
{
  private:
    GLuint vao, vbo;
    int vertices_count;
    std::vector< WMath::vec3 > vertices;
    std::vector< std::array<GLushort, 3> > elements;
    WMath::vec3 dimensions;
  public:
    Mesh( std::string file_path );
    void configureShader( std::shared_ptr<Shader> shader );
    // getters
    GLuint getVAO() { return this->vao; }
    GLuint getVBO() { return this->vbo; }
    const std::vector< WMath::vec3 > getVertices() { return this->vertices; }
    const std::vector< std::array< GLushort, 3 > > getElements()
      { return this->elements; }
    int getVerticesCount() { return this->vertices_count; }
    WMath::vec3 getDimensions() { return this->dimensions; }
};

#endif
