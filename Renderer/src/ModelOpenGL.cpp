#include "Renderer/ModelOpenGL.h"

ModelOpenGL::ModelOpenGL( ModelFileType model_file_type,
                          std::string file_path )
{
  // Create Vertex Array Object
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(vao);

  // Create a Vertex Buffer Object
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  if( model_file_type == OBJ )
  {
    std::vector< WMath::vec3 > vertices;
    std::vector< WMath::vec3 > normals;
    std::vector< GLuint > vertexIndices;
    std::vector< GLuint > normalIndices;
    std::vector< GLuint > uvIndices;

    ModelHelper::ImportOBJ(
        "cow.obj",
        &vertices,
        &normals,
        &vertexIndices,
        &normalIndices,
        &uvIndices
        );

    std::cout << "NUM_VERTICES: " << vertices.size() << std::endl;

    std::vector< WMath::vec3 > new_vertices;
    for( int i=0; i < vertexIndices.size(); i++ )
      new_vertices.push_back( vertices.at( vertexIndices.at(i) ) ) ;

    this->vertices_count = vertexIndices.size();

    glBufferData(GL_ARRAY_BUFFER, new_vertices.size() * sizeof(WMath::vec3),
                  &new_vertices[0], GL_STATIC_DRAW);
  }

  // Specify the layout of the vertex data
  this->shader.setVertexAttribute( "position", 3 );
  this->shader.setUniformMatrix4fv( "t", WMath::value_ptr( &this->transformation ), GL_TRUE );
  this->shader.setUniform3f( "color", 1.0f, 1.0f, 1.0f );

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void ModelOpenGL::before_draw()
{
  this->shader.before_draw();
  glBindVertexArray( this->vao );
}

void ModelOpenGL::after_draw()
{
  glBindVertexArray(0);
  this->shader.after_draw();
}

void ModelOpenGL::draw()
{
  this->before_draw();
  glDrawArrays(GL_TRIANGLES, 0, this->vertices_count);
  this->after_draw();
}

void ModelOpenGL::translate( WMath::vec3 vector )
{
  this->transformation = this->transformation * WMath::translate( vector );

  Camera camera( WMath::vec3(0.0f, 3.0f, 2.0f),
      WMath::vec3(0.0f, 0.0f, 0.0f) );

  WMath::mat4 view = camera.getView();

  WMath::mat4 proj = WMath::OpenGlPerspective( 45.0f, 800.0f/600.0f, 0.1f, 100.0f );

  this->shader.setUniformMatrix4fv( "t",
      WMath::value_ptr( &this->transformation ) , GL_TRUE);

  this->shader.setUniformMatrix4fv( "proj",
      WMath::value_ptr( &proj ), GL_FALSE);

  this->shader.setUniformMatrix4fv( "view",
      WMath::value_ptr( &view ), GL_FALSE);
}

void ModelOpenGL::scale( WMath::vec3 vector )
{
  this->transformation = this->transformation * WMath::scale( vector );

  this->shader.setUniformMatrix4fv( "t",
      WMath::value_ptr( &this->transformation ), GL_TRUE);
}

void ModelOpenGL::rotate( float degrees )
{
  this->transformation = this->transformation * WMath::rotate_y( degrees );

  this->shader.setUniformMatrix4fv( "t",
      WMath::value_ptr( &this->transformation ), GL_TRUE);
}
