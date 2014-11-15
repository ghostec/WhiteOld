#ifndef __RENDERER_MESHOPENGL__
#define __RENDERER_MESHOPENGL__

#include <iostream>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include "Renderer/Vertex.h"
#include "Renderer/Shader.h"
#include "Renderer/Helpers/ModelAssetHelper.h"
#include "WMath/WMath.h"
#include "WMath/transformations.h"
#include "Helpers/Application.h"

enum MeshType
{
  MESH_V2, MESH_V2N, MESH_V2T, MESH_V2NT,
  MESH_V3, MESH_V3N, MESH_V3T, MESH_V3NT
};

class Mesh
{
  private:
    GLuint vao, vbo;
    int vertices_count;
    std::vector< WMath::vec3 > vertices, normals, uvs;
    std::vector< std::array<GLushort, 3> > elements;
    WMath::vec3 dimensions;
    MeshType type;
    // methods
  public:
    Mesh( MeshType type );
    Mesh( std::string file_path );
    void use();
    void unuse();
    void resetVBO();
    // setters
    void setType( MeshType type ) { this->type = type; };
    void setVertices( std::vector< WMath::vec3 > v ) { this->vertices = v; }
    void setUVs( std::vector< WMath::vec3 > uvs ) { this->uvs = uvs; }
    // getters
    GLuint getVAO() { return this->vao; }
    GLuint getVBO() { return this->vbo; }
    const std::vector< WMath::vec3 > getVertices() { return this->vertices; }
    const std::vector< WMath::vec3 > getUVs() { return this->uvs; }
    const std::vector< std::array< GLushort, 3 > > getElements()
      { return this->elements; }
    int getVerticesCount() { return this->vertices_count; }
    WMath::vec3 getDimensions() { return this->dimensions; }
    MeshType getType() { return this->type; }
};

#endif
