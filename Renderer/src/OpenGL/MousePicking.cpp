#include "Renderer/OpenGL/MousePicking.h"

// encode an unique ID into a colour with components in range of 0.0 to 1.0
WMath::vec3 encode_id( int id )
{
  int r = id / 65536;
  int g = ( id - r * 65536 ) / 256;
  int b = ( id - r * 65536 - g * 256 );

  // convert to floats. only divide by 255, because range is 0-255
  return WMath::vec3( (float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f );
}

int decode_id( int r, int g, int b ) {
  return b + g * 256 + r * 256 * 256;
}

MousePicking::MousePicking()
{
  int width = 800;
  int height = 600;

  this->shader.reset( new Shader( "color_picking" ) );

  this->shader->use( );

  // create framebuffer
  this->frame_buffer = 0;
  glGenFramebuffers( 1, &this->frame_buffer );
  glBindFramebuffer( GL_FRAMEBUFFER, this->frame_buffer );

  // attach rendethis->render_bufferuffer to this->frame_buffer so that depth-sorting works
  this->render_buffer = 0;
  glGenRenderbuffers( 1, &this->render_buffer );
  glBindRenderbuffer( GL_RENDERBUFFER, this->render_buffer );
  glRenderbufferStorage(
    GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height
    );

  // create texture to use for rendering second pass
  this->frame_buffer_tex = 0;
  glGenTextures( 1, &this->frame_buffer_tex );
  glBindTexture( GL_TEXTURE_2D, this->frame_buffer_tex );
  // make the texture the same size as the viewport
  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGBA,
    width,
    height,
    0,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    NULL
    );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

  // attach render buffer (depth) and texture (colour) to this->frame_buffer
  glFramebufferRenderbuffer(
    GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->render_buffer
    );
  glFramebufferTexture2D(
    GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->frame_buffer_tex, 0
    );

  // redirect fragment shader output 0 used to the texture that we just bound
  GLenum draw_bufs[] = { GL_COLOR_ATTACHMENT0 };
  glDrawBuffers( 1, draw_bufs );

  this->shader->unuse( );

  // bind default this->frame_buffer (number 0) so that we render normally next time
  glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void MousePicking::setScene( std::shared_ptr<Scene> scene )
{
  this->scene = scene;
}

void MousePicking::draw_picker_colours() 
{
  int width = 800;
  int height = 600;

  glBindFramebuffer( GL_FRAMEBUFFER, this->frame_buffer );

  glViewport( 0, 0, width, height );
  glClearColor( 0.0, 0.0, 0.0, 1.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  this->shader->use();
  // TODO: Send matrices

  for( std::shared_ptr<ModelInstance> model_instance : *scene->getModelInstances( ) )
  {
    model_instance->getModelAsset()->configureShader( this->shader );
    WMath::vec3 picking_color = encode_id( model_instance->getPickingId() );
    this->shader->setUniform3f( "unique_id", picking_color[0], picking_color[1], picking_color[2] );
    model_instance->getModelAsset()->before_draw();
    std::vector< std::shared_ptr<Shader> > shaders { this->shader };
    this->shader->setUniformMatrix4fv( "Model", WMath::value_ptr( model_instance->getTransformM() ), GL_TRUE );
    ShaderHelper::setCamera( &*this->shader, &*scene->getCamera() );
    model_instance->getModelAsset()->drawWithShaders( &shaders );
    model_instance->getModelAsset()->after_draw();
  }
  this->shader->unuse( );

  glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

int MousePicking::getIdForPosition( int x, int y )
{
  int width = 800;
  int height = 600;

  this->draw_picker_colours();

  glBindFramebuffer( GL_FRAMEBUFFER, this->frame_buffer );
  unsigned char data[4] = { 0, 0, 0, 0 };
  glReadPixels( x, height - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data );
  glBindFramebuffer( GL_FRAMEBUFFER, 0 );

  return decode_id( (int) data[0], (int) data[1], (int) data[2] );
}