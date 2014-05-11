#include "Input/GLFW/Input.h"

void Input::setWindow( Window *window )
{
  this->context.window = window;
}

Input::Input( GLFWcontext context )
{
  this->setWindow( context.window );
}

bool Input::isKeyPressed( Key key )
{
  return GLFWhelper::isKeyPressed( this->context.window->getWindow(), key );
}
