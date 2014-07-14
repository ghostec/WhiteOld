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

void Input::getMousePos( int* x, int* y )
{
  double xpos, ypos;
  glfwGetCursorPos( this->window, &xpos, &ypos );
  *x = (int) xpos;
  *y = (int) ypos;
}

void keyboardCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
  if( action == GLFW_PRESS )
  {
    active_input->addKey( key );
    //active_input->notify( "KEY_PRESSED" );
  }
  else if( action == GLFW_RELEASE )
  {
    active_input->removeKey( key );
    //active_input->notify( "KEY_RELEASED" );
  }
}

void mouseButtonCallback( GLFWwindow* window, int button, int action, int mods )
{
  if( action == GLFW_PRESS ) active_input->notify( "CLICK" );
}