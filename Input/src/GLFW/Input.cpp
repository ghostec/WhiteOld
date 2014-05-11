#include "Input/GLFW/Input.h"

Input* active_input;

Input::Input( GLFWwindow* window )
{
  this->window = window;
}

bool Input::isKeyPressed( Key key )
{
  return GLFWhelper::isKeyPressed( this->window, key );
}

void keyboardCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
  active_input->notify( "test" );
}