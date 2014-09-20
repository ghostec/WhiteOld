#include "Renderer/OpenGL/Mesh.h"

Mesh::Mesh( std::string file_path )
{
  // Create Vertex Array Object
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(vao);

  // Create a Vertex Buffer Object
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  std::vector< WMath::vec3 > uvs, normals;

  file_path = "../assets/models/" + file_path;
  ModelAssetHelper::ImportOBJ( file_path.c_str(),
    this->vertices, uvs, normals, this->elements );

  this->dimensions = ModelAssetHelper::calculateDimensions( vertices );

  std::vector< WMath::vec3 > new_vertices;
  for( int i = 0; i < elements.size(); i++ )
  {
    new_vertices.push_back( vertices.at( elements.at( i )[0] ) );
    new_vertices.push_back( uvs.at( elements.at( i )[1] ) );
    new_vertices.push_back( normals.at( elements.at( i )[2] ) );
  }

  this->vertices_count = elements.size();

  glBufferData( GL_ARRAY_BUFFER,
    elements.size() * ( 3 * sizeof( WMath::vec3 ) ),
    &new_vertices[0], GL_STATIC_DRAW );

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}