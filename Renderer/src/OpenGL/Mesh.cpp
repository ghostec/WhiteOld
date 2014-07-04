#include "Renderer/OpenGL/Mesh.h"

Mesh::Mesh( std::string file_path )
{
  // Create Vertex Array Object
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(vao);

  // Create a Vertex Buffer Object
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  std::vector< WMath::vec3 > vertices, uvs, normals;
  std::vector< std::array<GLushort, 3> > elements;

  file_path = "../assets/models/" + file_path;
  ModelAssetHelper::ImportOBJ( file_path.c_str(),
    vertices, uvs, normals, elements );

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

void Mesh::configureShader( std::shared_ptr<Shader> shader )
{
  glBindVertexArray( this->vao );
  glBindBuffer( GL_ARRAY_BUFFER, this->vbo );

  shader->setVertexAttribute( "vPosition", 3, 3 * sizeof( WMath::vec3 ),
    0 );
  shader->setVertexAttribute( "vUV", 3, 3 * sizeof( WMath::vec3 ),
    sizeof( WMath::vec3 ) );
  shader->setVertexAttribute( "vNormal", 3, 3 * sizeof( WMath::vec3 ),
    2 * sizeof( WMath::vec3 ) );

  glBindBuffer( GL_ARRAY_BUFFER, 0 );
  glBindVertexArray( 0 );
}