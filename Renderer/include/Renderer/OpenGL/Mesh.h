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

enum MeshIndexingType
{
  MESH_INDEXED, MESH_NOT_INDEXED
};

enum MeshType
{
  MESH_V2, MESH_V2N, MESH_V2T, MESH_V2NT,
  MESH_V3, MESH_V3N, MESH_V3T, MESH_V3NT
};

class Mesh
{
  private:
    GLuint vao, vbo, ebo;
    std::vector< WMath::vec3 > vertices, normals, uvs;
    std::vector< int > indices;
    WMath::vec3 dimensions;
    MeshType type;
    MeshIndexingType indexing_type;
    // methods
  public:
    Mesh( MeshType type, MeshIndexingType indexing_type );
    Mesh( std::string file_path );
    void use();
    void unuse();
    void resetVBO();
    // setters
    void setType( MeshType type ) { this->type = type; };
    void setIndexingType( MeshIndexingType indexing_type )
    { this->indexing_type = indexing_type; }
    void setVertices( std::vector< WMath::vec3 > v ) { this->vertices = v; }
    void setUVs( std::vector< WMath::vec3 > uvs ) { this->uvs = uvs; }
    void setIndices( std::vector< int > indices ) { this->indices = indices; }
    // getters
    GLuint getVAO() { return this->vao; }
    GLuint getVBO() { return this->vbo; }
    GLuint getEBO() { return this->ebo; }
    std::vector< WMath::vec3 >& getVertices() { return this->vertices; }
    std::vector< WMath::vec3 >& getUVs() { return this->uvs; }
    std::vector< int >& getIndices() { return this->indices; }
    int getVerticesCount() { return this->vertices.size(); }
    WMath::vec3 getDimensions() { return this->dimensions; }
    MeshType getType() { return this->type; }
    MeshIndexingType getIndexingType() { return this->indexing_type; }
};

#endif
