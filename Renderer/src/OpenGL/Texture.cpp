#include "Renderer/OpenGL/Texture.h"

Texture::Texture( std::string name )
{
  glGenTextures( 1, &this->texture );

  int width, height;
  unsigned char* image;
  std::string path = "../assets/textures/" + name;

  glActiveTexture( GL_TEXTURE0 );
  glBindTexture( GL_TEXTURE_2D, this->texture );

  image = SOIL_load_image( path.c_str( ), &width, &height, 0, SOIL_LOAD_RGBA );
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
  SOIL_free_image_data( image );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
  glGenerateMipmap( GL_TEXTURE_2D );
  glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  glBindTexture( GL_TEXTURE_2D, 0 );
}

void Texture::use( Shader* shader )
{
  glBindTexture( GL_TEXTURE_2D, this->texture );
  glUniform1i( glGetUniformLocation( shader->shader, "materialTex" ), 0 );
}

void Texture::unuse()
{
  glBindTexture( GL_TEXTURE_2D, 0 );
}