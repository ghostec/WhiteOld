#include "Renderer/OpenGL/Shader.h"

Shader::Shader( std::string name )
{
  this->shader = MeshHelper::OpenGL::CreateShaderProgram(
    "../assets/shaders/" + name + "/vertex.glsl",
    "../assets/shaders/" + name + "/fragment.glsl",
    "../assets/shaders/" + name + "/geometry.glsl" );

  this->name      = name;
}

void Shader::use()
{
  glUseProgram( this->shader );
}

void Shader::unuse()
{
  glUseProgram(0);
}

void Shader::setVertexAttribute(  std::string name, int count, int stride,
    int offset )
{
  glUseProgram(this->shader);
  GLint attribute = glGetAttribLocation( this->shader, name.c_str() );
  glEnableVertexAttribArray( attribute );
  glVertexAttribPointer(  attribute, count, GL_FLOAT, GL_FALSE, stride,
      (void*) offset );
  glUseProgram(0);
}

void Shader::setUniform( std::string name, const int value )
{
  glUseProgram( this->shader );
  GLint uniform = glGetUniformLocation( this->shader, name.c_str() );
  glUniform1i( uniform, value );
  glUseProgram( 0 );
}

void Shader::setUniform( std::string name, const float value )
{
  glUseProgram( this->shader );
  GLint uniform = glGetUniformLocation( this->shader, name.c_str( ) );
  glUniform1f( uniform, value );
  glUseProgram( 0 );
}

void Shader::setUniform( std::string name, const float value[3] )
{
  glUseProgram( this->shader );
  GLint uniform = glGetUniformLocation( this->shader, name.c_str( ) );
  glUniform3f( uniform, value[0], value[1], value[2] );
  glUseProgram( 0 );
}

void Shader::setUniform( std::string name, WMath::vec4 value )
{
  glUseProgram( this->shader );
  GLint uniform = glGetUniformLocation( this->shader, name.c_str() );
  glUniform4f( uniform, value[ 0 ], value[ 1 ], value[ 2 ], value[ 3 ] );
  glUseProgram( 0 );
}

void Shader::setUniform( std::string name, WMath::mat4* value,
    bool transpose )
{
  glUseProgram(this->shader);
  GLint uniform = glGetUniformLocation( this->shader , name.c_str() );
  glUniformMatrix4fv( uniform, 1, transpose, WMath::value_ptr( value ) );
  glUseProgram(0);
}
