#include "Renderer/ModelOpenGL.h"

ModelOpenGL::ModelOpenGL( ModelFileType model_file_type,
                          std::string file_path )
{
  if( model_file_type == OBJ ) ModelHelper::ImportOBJ();

  // Create Vertex Array Object
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(vao);

  // Create a Vertex Buffer Object
  glGenBuffers(1, &this->vbo);

  GLfloat vertices[] = {
  // Front face
    -1.0, -1.0,  1.0,
     1.0, -1.0,  1.0,
     1.0,  1.0,  1.0,
    -1.0,  1.0,  1.0,
    
    // Back face
    -1.0, -1.0, -1.0,
    -1.0,  1.0, -1.0,
     1.0,  1.0, -1.0,
     1.0, -1.0, -1.0,
    
    // Top face
    -1.0,  1.0, -1.0,
    -1.0,  1.0,  1.0,
     1.0,  1.0,  1.0,
     1.0,  1.0, -1.0,
    
    // Bottom face
    -1.0, -1.0, -1.0,
     1.0, -1.0, -1.0,
     1.0, -1.0,  1.0,
    -1.0, -1.0,  1.0,
    
    // Right face
     1.0, -1.0, -1.0,
     1.0,  1.0, -1.0,
     1.0,  1.0,  1.0,
     1.0, -1.0,  1.0,
    
    // Left face
    -1.0, -1.0, -1.0,
    -1.0, -1.0,  1.0,
    -1.0,  1.0,  1.0,
    -1.0,  1.0, -1.0
  };

  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  this->shader_program = ModelHelper::OpenGL::CreateShaderProgram(
      "../Renderer/shaders/vertex_shader.glsl",
      "../Renderer/shaders/fragment_shader.glsl" );

  glUseProgram(shader_program);
  // Specify the layout of the vertex data
  setVertexAttribute( shader_program, "position" );

  GLint uniTrans = glGetUniformLocation(shader_program, "t");
  glUniformMatrix4fv( uniTrans, 1, GL_TRUE, WMath::value_ptr( &this->transformation ) );
  glUseProgram(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void ModelOpenGL::setVertexAttribute( GLuint shader_program,
    std::string attrib_name )
{
  GLint posAttrib = glGetAttribLocation(shader_program, attrib_name.c_str() );
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void ModelOpenGL::draw()
{
  glBindVertexArray( this->vao );
  glUseProgram( this->shader_program );

  glDrawArrays(GL_TRIANGLES, 0, 6*7);

  glUseProgram(0);
  glBindVertexArray(0);
}

void ModelOpenGL::translate( WMath::vec3 vector )
{
  this->transformation = this->transformation * WMath::translate( vector );

  WMath::mat4 view = WMath::lookAtRH( WMath::vec3(0.3f, 0.0f, -2.0f),
      WMath::vec3(0.0f, 0.0f, -4.0f),
      WMath::vec3(0.0f, 1.0f, 0.0f) );

  WMath::mat4 proj = WMath::OpenGlPerspective( 45.0f, 800.0f/600.0f, 0.1f, 100.0f );

  glUseProgram( this->shader_program );
  GLint uniTrans = glGetUniformLocation(shader_program, "t");
  glUniformMatrix4fv( uniTrans, 1, GL_TRUE, WMath::value_ptr( &this->transformation ) );
  GLint uniProj = glGetUniformLocation(shader_program, "proj");
  glUniformMatrix4fv( uniProj, 1, GL_FALSE, WMath::value_ptr( &proj ) );
  GLint uniView = glGetUniformLocation(shader_program, "view");
  glUniformMatrix4fv( uniView, 1, GL_FALSE, WMath::value_ptr( &view) );
  glUseProgram(0);
}

void ModelOpenGL::scale( WMath::vec3 vector )
{
  this->transformation = this->transformation * WMath::scale( vector );

  glUseProgram( this->shader_program );
  GLint uniTrans = glGetUniformLocation(shader_program, "t");
  glUniformMatrix4fv( uniTrans, 1, GL_TRUE, WMath::value_ptr( &this->transformation ) );
  glUseProgram(0);
}

void ModelOpenGL::rotate( float degrees )
{
  this->transformation = this->transformation * WMath::rotate_y( degrees );

  glUseProgram( this->shader_program );
  GLint uniTrans = glGetUniformLocation(shader_program, "t");
  glUniformMatrix4fv( uniTrans, 1, GL_TRUE, WMath::value_ptr( &this->transformation ) );
  glUseProgram(0);
}
