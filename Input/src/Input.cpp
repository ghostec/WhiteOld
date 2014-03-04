#include "Input/Input.h"

void InputGLFW::setWindow( Window *window )
{
  this->context.window = window;
}

InputGLFW::InputGLFW( GLFWcontext context )
{
  this->setWindow( context.window );
}

bool InputGLFW::isKeyPressed( Key key )
{
  return GLFWhelper::isKeyPressed( this->context.window->getWindow(), key );
}
