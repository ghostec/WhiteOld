#include "Renderer/ShaderGLSL.h"

ShaderGLSL::ShaderGLSL()
{
  this->shader = ModelHelper::OpenGL::CreateShaderProgram(
      "../Renderer/shaders/vertex_shader.glsl",
      "../Renderer/shaders/fragment_shader.glsl" );
}

void ShaderGLSL::before_draw()
{
  glUseProgram( this->shader );
}

void ShaderGLSL::after_draw()
{
  glUseProgram(0);
}

void ShaderGLSL::setVertexAttribute( std::string name, int count )
{
  glUseProgram(this->shader);
  GLint attribute = glGetAttribLocation( this->shader, name.c_str() );
  glEnableVertexAttribArray( attribute );
  glVertexAttribPointer( attribute, count, GL_FLOAT, GL_FALSE, 0, 0 );
  glUseProgram(0);
}

void ShaderGLSL::setUniformMatrix4fv( std::string name,
                                      const GLfloat *value,
                                      GLboolean transpose )
{
  glUseProgram(this->shader);
  GLint uniform = glGetUniformLocation( this->shader , name.c_str() );
  glUniformMatrix4fv( uniform, 1, transpose, value );
  glUseProgram(0);
}