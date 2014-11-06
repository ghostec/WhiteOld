#include "Renderer/OpenGL/MousePicking.h"

MousePicking* active_mouse_picking;

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
  this->shader.reset( new Shader( "color_picking" ) );
}

void MousePicking::reset()
{
  this->viewport_dimensions =
    this->viewport->getContainableCachedData().dimensions;

  this->shader->use();

  // create framebuffer
  this->frame_buffer = 0;
  glGenFramebuffers( 1, &this->frame_buffer );
  glBindFramebuffer( GL_FRAMEBUFFER, this->frame_buffer );

  // attach this->render_bufferuffer to this->frame_buffer so that depth-sorting works
  this->render_buffer = 0;
  glGenRenderbuffers( 1, &this->render_buffer );
  glBindRenderbuffer( GL_RENDERBUFFER, this->render_buffer );
  glRenderbufferStorage
    ( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->viewport_dimensions[0], this->viewport_dimensions[1] );

  // create texture to use for rendering second pass
  this->frame_buffer_tex = 0;
  glGenTextures( 1, &this->frame_buffer_tex );
  glBindTexture( GL_TEXTURE_2D, this->frame_buffer_tex );
  // make the texture the same size as the viewport
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, this->viewport_dimensions[0], this->viewport_dimensions[1], 0, GL_RGBA,
    GL_UNSIGNED_BYTE, NULL );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

  // attach render buffer (depth) and texture (colour) to this->frame_buffer
  glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
    GL_RENDERBUFFER, this->render_buffer );
  glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
    this->frame_buffer_tex, 0 );

  // redirect fragment shader output 0 used to the texture that we just bound
  GLenum draw_bufs[] = { GL_COLOR_ATTACHMENT0 };
  glDrawBuffers( 1, draw_bufs );

  this->shader->unuse();

  // bind default this->frame_buffer (number 0) so that we render normally next time
  glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void MousePicking::drawViewport( Viewport* viewport, WMath::vec2 cursor_position )
{
  glBindFramebuffer( GL_FRAMEBUFFER, 0 );
  this->node_count = 1000;

  ContainableIterator<Viewport, Window> it( &*this->viewport, active_window );

  for( Viewport* v = it.begin(); v != nullptr; v = it.next() )
  {
    ContainableCachedData viewport_cached_data = v->getContainableCachedData();

    glEnable( GL_SCISSOR_TEST );
    glScissor( viewport_cached_data.anchor[0],
      active_window->getDimensions()[1] - viewport_cached_data.dimensions[1]
      - viewport_cached_data.anchor[1],
      viewport_cached_data.dimensions[0], viewport_cached_data.dimensions[1] );

    glViewport( viewport_cached_data.anchor[0],
        active_window->getDimensions()[1] - viewport_cached_data.dimensions[1]
        - viewport_cached_data.anchor[1],
        viewport_cached_data.dimensions[0], viewport_cached_data.dimensions[1] );
    glClearColor( viewport_cached_data.background[0],
        viewport_cached_data.background[1],
        viewport_cached_data.background[2], 1.0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    for( auto scene : v->getScenes() )
    {
      this->drawScene( &*scene, viewport_cached_data );
    }

    glDisable( GL_SCISSOR_TEST );
  }

  glfwSwapBuffers( active_window->getWindow() );
  glfwPollEvents();

  glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void MousePicking::drawScene( Scene* scene, ContainableCachedData viewport_cached_data )
{
  ShaderHelper::setCamera( &*this->shader, &*scene->getCamera() );

  SGNodeIterator it( &*scene->getSceneGraph()->getRootSGNode() );

  // Problem is on shader initialization
  // Model::use()

  for( SGNode* n = it.begin(); n; n = it.next(), node_count++ )
  {
    WMath::vec3 picking_color = encode_id( node_count );
    this->shader->setUniform( "unique_id", picking_color.vec );
    RendererHelper::drawSGNode( n, &*this->shader );
  }
}

std::shared_ptr<SGNode> MousePicking::pick()
{
  WMath::vec2 cursor_position = active_input->getMousePos();
  int x = cursor_position[0];
  int y = cursor_position[1];

  this->reset();
  this->drawViewport( &*this->viewport, cursor_position );

  glBindFramebuffer( GL_FRAMEBUFFER, this->frame_buffer );
  unsigned char data[4] = { 0, 0, 0, 0 };
  glReadPixels( x, this->viewport_dimensions[1] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data );
  glBindFramebuffer( GL_FRAMEBUFFER, 0 );

  int node_index = decode_id( (int) data[0], (int) data[1], (int) data[2] );

  int current_index = 1;

  if( node_index != 0 )
  {
    ContainableIterator<Viewport, Window> it( &*this->viewport, active_window );

    for( Viewport* v = it.begin( ); v != nullptr; v = it.next( ) )
    {
      for( auto scene : v->getScenes() )
      {
        std::queue< std::shared_ptr<SGNode> > bfs_q;
        std::vector< std::shared_ptr<SGNode> > bfs_v;

        bfs_q.push( scene->getSceneGraph( )->getRootSGNode( ) );
        bfs_v.push_back( bfs_q.front( ) );

        while( !bfs_q.empty( ) )
        {
          std::shared_ptr<SGNode> sg_node = bfs_q.front(); bfs_q.pop();

          if( current_index == node_index ) return sg_node;

          for( auto c : sg_node->getChildren( ) )
          {
            if( std::find( bfs_v.begin( ), bfs_v.end( ), c ) == bfs_v.end( ) )
            {
              bfs_q.push( c ); bfs_v.push_back( c );
            }
          }

          current_index += 1;
        }
      }
    }
  }

  return nullptr;
}
