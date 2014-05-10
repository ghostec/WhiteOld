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

    std::vector< WMath::vec3 > new_vertices;
    for( int i=0; i < vertexIndices.size(); i++ )
      new_vertices.push_back( vertices.at( vertexIndices.at(i) ) ) ;

    this->model_data.vertices_count = vertexIndices.size();

    glBufferData(GL_ARRAY_BUFFER, new_vertices.size() * sizeof(WMath::vec3),
                  &new_vertices[0], GL_STATIC_DRAW);

  // Specify the layout of the vertex data
  this->shader.setVertexAttribute( "position", 3 );
  this->shader.setUniformMatrix4fv( "t", WMath::value_ptr( &this->model_data.transformation ), GL_TRUE);
  this->shader.setUniform3f( "color", 1.0f, 1.0f, 1.0f );

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Model::before_draw()
{
  this->shader.setUniformMatrix4fv( "t",
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

void Model::translate( WMath::vec3 vector )
{
  WMath::translate( &this->model_data.transformation, vector );

  Camera camera(WMath::vec3(0.0f, 3.0f, 2.0f),
    WMath::vec3(0.0f, 0.0f, 0.0f));

  WMath::mat4 view = camera.getView();

  WMath::mat4 proj = WMath::OpenGlPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

  this->shader.setUniformMatrix4fv("proj",
    WMath::value_ptr(&proj), GL_FALSE);

  this->shader.setUniformMatrix4fv("view",
    WMath::value_ptr(&view), GL_FALSE);
}

void Model::scale( WMath::vec3 vector )
{
  WMath::scale( &this->model_data.transformation, vector );
}

void Model::rotate( float degrees )
{
  WMath::rotate_y( &this->model_data.transformation, degrees );
}
