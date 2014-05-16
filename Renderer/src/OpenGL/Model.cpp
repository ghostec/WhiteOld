#include "Renderer/OpenGL/Model.h"

Model::Model( std::string file_path )
{
  // Create Vertex Array Object
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(vao);

  // Create a Vertex Buffer Object
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  std::vector< WMath::vec4 > vertices;
  std::vector< WMath::vec3 > normals;
  std::vector< GLushort > elements;

  ModelHelper::ImportOBJ(
      file_path.c_str(),
      vertices,
      normals,
      elements
      );

  float max = 0.0f;
  for( int i = 0; i < vertices.size(); i++ )
  {
    for( int j = 0; j < 3; j++ )
    {
      if( vertices[i][j] > max ) max = vertices[i][j];
    }
  }
  for( int i = 0; i < vertices.size( ); i++ )
  {
    for( int j = 0; j < 3; j++ )
    {
      vertices[i][j] /= max;
    }
  }

  std::vector< WMath::vec3 > new_vertices;
  for( int i = 0; i < elements.size(); i++ )
  {
    new_vertices.push_back( WMath::vec3( vertices.at( elements.at( i ) ) ) );
    new_vertices.push_back( normals.at( elements.at( i ) ) );
  }

  this->model_data.vertices_count = elements.size();

  glBufferData( GL_ARRAY_BUFFER, elements.size() * ( sizeof( WMath::vec3 ) + sizeof( WMath::vec3 ) ),
                &new_vertices[0], GL_STATIC_DRAW);

  // Specify the layout of the vertex data
  this->shader.setVertexAttribute(  "position", 3, sizeof( WMath::vec3 ) + sizeof( WMath::vec3 ),
                                    0);
  this->shader.setVertexAttribute(  "normal", 3, sizeof( WMath::vec3 ) + sizeof( WMath::vec3 ),
                                    sizeof( WMath::vec3 ) );
  this->shader.setUniformMatrix4fv( "transformation", WMath::value_ptr(
                                          &this->model_data.transformation ),
                                    GL_TRUE );

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Model::before_draw()
{
  this->shader.setUniformMatrix4fv( "transformation",
              WMath::value_ptr( &this->model_data.transformation ), GL_TRUE );
  this->shader.before_draw();
  glBindVertexArray( this->vao );
}

void Model::after_draw()
{
  glBindVertexArray(0);
  this->shader.after_draw();
}

void Model::draw()
{
  this->before_draw();
  glDrawArrays( GL_TRIANGLES, 0, this->model_data.vertices_count );
  this->after_draw();
}

void Model::setView( WMath::mat4* view )
{
  this->shader.setUniformMatrix4fv( "view",
                                    WMath::value_ptr(view), GL_FALSE);
}

void Model::setProj( WMath::mat4* proj )
{
  this->shader.setUniformMatrix4fv( "proj",
                                    WMath::value_ptr(proj), GL_FALSE);
}

void Model::move()
{
  if( this->moves.ARROW_UP )
    WMath::translate( &this->model_data.transformation, WMath::vec3( 0.0f, 0.005f, 0.0f ) );
  if( this->moves.ARROW_DOWN )
    WMath::translate( &this->model_data.transformation, WMath::vec3( 0.0f, -0.005f, 0.0f ) );
}