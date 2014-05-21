#include "Renderer/OpenGL/Model.h"

Model::Model( std::string file_path )
{
  // Create Vertex Array Object
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(vao);

  // Create a Vertex Buffer Object
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  std::vector< WMath::vec3 > vertices;
  std::vector< WMath::vec3 > uvs;
  std::vector< WMath::vec3 > normals;
  std::vector< std::array<GLushort, 3> > elements;

  ModelHelper::ImportOBJ( file_path.c_str(), vertices, uvs, normals, elements );
  normals = ModelHelper::CalculateNormalsAveraged( vertices, elements );

  std::vector< WMath::vec3 > new_vertices;
  for( int i = 0; i < elements.size(); i++ )
  {
    new_vertices.push_back( vertices.at( elements.at( i )[0] ) );
    new_vertices.push_back( uvs.at( elements.at( i )[1] ) );
    new_vertices.push_back( normals.at( elements.at( i )[0] ) );
  }

  this->model_data.vertices_count = elements.size();

  glBufferData( GL_ARRAY_BUFFER, elements.size() * ( 3 * sizeof( WMath::vec3 ) ),
                &new_vertices[0], GL_STATIC_DRAW);

  // Specify the layout of the vertex data
  this->shader.setVertexAttribute(  "vPosition", 3, 3 * sizeof( WMath::vec3 ),
                                    0);
  this->shader.setVertexAttribute( "vUV", 3, 3 * sizeof( WMath::vec3 ),
                                   sizeof( WMath::vec3 ) );
  this->shader.setVertexAttribute( "vNormal", 3, 3 * sizeof( WMath::vec3 ),
                                    2 * sizeof( WMath::vec3 ) );
  this->shader.setUniformMatrix4fv( "Model", WMath::value_ptr(
                                          &this->model_data.transformation ),
                                    GL_TRUE );

  // Load textures
  GLuint textures[2];
  glGenTextures( 2, textures );

  int width, height;
  unsigned char* image;

  glActiveTexture( GL_TEXTURE0 );
  glBindTexture( GL_TEXTURE_2D, textures[0] );
  image = SOIL_load_image( "../assets/textures/wooden-crate.jpg", &width, &height, 0, SOIL_LOAD_RGB );
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
  SOIL_free_image_data( image );
  glUniform1i( glGetUniformLocation( this->shader.shader, "materialTex" ), 0 );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Model::before_draw()
{
  this->shader.setUniformMatrix4fv( "Model",
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

void Model::move()
{
  if( this->moves.ARROW_UP )
    WMath::translate( &this->model_data.transformation, WMath::vec3( 0.0f, 0.005f, 0.0f ) );
  if( this->moves.ARROW_DOWN )
    WMath::translate( &this->model_data.transformation, WMath::vec3( 0.0f, -0.005f, 0.0f ) );
}