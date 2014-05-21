#include "Renderer/OpenGL/Shader.h"

Shader::Shader()
{
  this->shader = ModelHelper::OpenGL::CreateShaderProgram(
      "../assets/shaders/vertex_shader.glsl",
      "../assets/shaders/fragment_shader.glsl" );
}

void Shader::before_draw()
{
  glUseProgram( this->shader );
}

void Shader::after_draw()
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

void Shader::setUniform1f( std::string name, GLfloat v0 )
{
  glUseProgram( this->shader );
  GLint uniform = glGetUniformLocation( this->shader, name.c_str( ) );
  glUniform1f( uniform, v0 );
  glUseProgram( 0 );
}

void Shader::setUniform3f(  std::string name,
                            GLfloat v0,
                            GLfloat v1,
                            GLfloat v2 )
{
  glUseProgram(this->shader);
  GLint uniform = glGetUniformLocation( this->shader , name.c_str() );
  glUniform3f( uniform, v0, v1, v2 );
  glUseProgram(0);
}

void Shader::setUniformMatrix4fv( std::string name,
                                  const GLfloat *value,
                                  GLboolean transpose )
{
  glUseProgram(this->shader);
  GLint uniform = glGetUniformLocation( this->shader , name.c_str() );
  glUniformMatrix4fv( uniform, 1, transpose, value );
  glUseProgram(0);
}

void Shader::setLight( Light* light )
{
  WMath::vec3 pos = light->getPosition( );
  this->setUniform3f( "light.position", pos[0], pos[1], pos[2] );
  this->setUniform3f( "light.intensities", 1.0f, 1.0f, 1.0f );
  this->setUniform1f( "light.attenuation", 0.2f );
  this->setUniform1f( "light.ambientCoefficient", 0.005f );
}

void Shader::setCamera( Camera* camera )
{
  this->setUniformMatrix4fv( "camera.view",
    WMath::value_ptr( camera->getView() ), GL_FALSE );
  this->setUniformMatrix4fv( "camera.proj",
    WMath::value_ptr( camera->getProj() ), GL_FALSE );
}