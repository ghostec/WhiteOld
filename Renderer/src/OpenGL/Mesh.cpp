#include "Renderer/OpenGL/Mesh.h"

Mesh::Mesh( MeshType type, MeshIndexingType indexing_type )
{
  this->type = type;
  this->indexing_type = indexing_type;
  glGenVertexArrays(1, &this->vao);
  glGenBuffers(1, &this->vbo);
}

Mesh::Mesh( std::string file_path )
{
  this->type = MESH_V3NT;
  this->indexing_type = MESH_NOT_INDEXED;

  glGenVertexArrays(1, &this->vao);
  glGenBuffers(1, &this->vbo);

  std::vector< std::array<GLushort, 3> > elements;

  file_path = "../assets/models/" + file_path;
  MeshHelper::ImportOBJ( file_path.c_str(),
    this->vertices, this->uvs, this->normals, elements );

  this->dimensions = MeshHelper::calculateDimensions( vertices );

  this->resetVBO();
}

void Mesh::resetVBO()
{
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  if( this->type == MESH_V3NT )
  {
    std::vector< WMath::vec3 > data;
    for( int i = 0; i < this->vertices.size(); i++ )
    {
      data.push_back( this->vertices[ i ] );
      data.push_back( this->uvs[ i ] );
      data.push_back( this->normals[ i ] );
    }

    glBufferData( GL_ARRAY_BUFFER,
        data.size() * sizeof( WMath::vec3 ),
        &data[0], GL_STATIC_DRAW );
  }
  else if( this->type == MESH_V2T )
  {
    std::vector< WMath::vec4 > data;

    for( int i = 0; i < this->vertices.size(); i++ )
    {
      WMath::vec4 v
        ( this->vertices[i][0], this->vertices[i][1],
          this->uvs[i][0], this->uvs[i][1] );
      data.push_back( v );
    }

    glBufferData( GL_ARRAY_BUFFER,
        this->vertices.size() * ( sizeof( WMath::vec4 ) ),
        &data[0], GL_DYNAMIC_DRAW );
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Mesh::use()
{
  glBindVertexArray( this->vao );
}

void Mesh::unuse()
{
  glBindVertexArray( 0 );
}
