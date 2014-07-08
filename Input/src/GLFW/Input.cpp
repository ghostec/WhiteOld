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
  if( key == GLFW_KEY_UP && action == GLFW_PRESS )
  {
    active_input->notify( "ARROW_UP_PRESS" );
  }
  else if( key == GLFW_KEY_UP && action == GLFW_RELEASE )
  {
    active_input->notify( "ARROW_UP_RELEASE" );
  }
  else if( key == GLFW_KEY_DOWN && action == GLFW_PRESS )
  {
    active_input->notify( "ARROW_DOWN_PRESS" );
  }
  else if( key == GLFW_KEY_DOWN && action == GLFW_RELEASE )
  {
    active_input->notify( "ARROW_DOWN_RELEASE" );
  }
}

void mouseButtonCallback( GLFWwindow* window, int button, int action, int mods )
{
  if( action == GLFW_PRESS ) active_input->notify( "CLICK" );
}