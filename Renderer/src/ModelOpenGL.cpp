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
    0.0f, 0.5f,
    0.5f, -0.5f,
    -0.5f, -0.5f
  };

  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  this->shader_program = ModelHelper::OpenGL::CreateShaderProgram(
                          "../Renderer/shaders/vertex_shader.glsl",
                          "../Renderer/shaders/fragment_shader.glsl" );

  glUseProgram(shader_program);
  // Specify the layout of the vertex data
  setVertexAttribute( shader_program, "position" );

  WMath::mat4 s = WMath::scale( WMath::vec3( 0.2f, 0.2f, 0.0f ) );
  WMath::mat4 t = WMath::translate( WMath::vec3( 0.5f, 0.7f, 0.0f ) );
  WMath::mat4 r = WMath::rotate_z( -90.0f );
  WMath::mat4 trans = t * r * s;

  GLint uniTrans = glGetUniformLocation(shader_program, "t");
  glUniformMatrix4fv( uniTrans, 1, GL_TRUE, WMath::value_ptr( &trans ) );
}

void ModelOpenGL::setVertexAttribute( GLuint shader_program,
                                      std::string attrib_name )
{
  GLint posAttrib = glGetAttribLocation(shader_program, attrib_name.c_str() );
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void ModelOpenGL::draw()
{
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ModelOpenGL::translate( WMath::vec3 vector )
{
  std::cout << "Placeholder ModelOpenGL::translate()" << std::endl;
}

void ModelOpenGL::scale( WMath::vec3 vector )
{
  std::cout << "Placeholder ModelOpenGL::scale()" << std::endl;
}

void ModelOpenGL::rotate( float degrees, WMath::vec3 vector )
{
  std::cout << "Placeholder ModelOpenGL::rotate()" << std::endl;
}
