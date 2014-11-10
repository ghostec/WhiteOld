#include "Renderer/OpenGL/Mesh.h"

Mesh::Mesh( MeshType type )
{
  this->type = type;
  glGenVertexArrays(1, &this->vao);
  glGenBuffers(1, &this->vbo);
}

Mesh::Mesh( std::string file_path )
{
  this->type = MESH_V3NT;

  glGenVertexArrays(1, &this->vao);
  glGenBuffers(1, &this->vbo);

  file_path = "../assets/models/" + file_path;
  ModelAssetHelper::ImportOBJ( file_path.c_str(),
    this->vertices, this->uvs, this->normals, this->elements );

  this->dimensions = ModelAssetHelper::calculateDimensions( vertices );

  this->resetVBO();
}

void Mesh::resetVBO()
{
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  if( this->type == MESH_V3NT )
  {
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
  }
  else if( this->type == MESH_V2T )
  {
    std::vector< WMath::vec4 > data;
    for( int i = 0; i < this->vertices.size(); i++ )
    {
      WMath::vec4 v
        ( this->vertices[i][0], this->vertices[i][1],
          this->uvs[i][0], this->uvs[i][1] );
      std::cout << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << " " << std::endl;
      data.push_back( v );
    }

    this->vertices_count = vertices.size();

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
