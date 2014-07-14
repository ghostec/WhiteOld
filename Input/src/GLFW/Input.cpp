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

WMath::vec2 Input::getMousePos()
{
  double xpos, ypos;
  glfwGetCursorPos( this->window, &xpos, &ypos );
  return WMath::vec2( xpos, ypos );
}

void Input::setMouseScroll( WMath::vec2 mouse_scroll_offset )
{
  this->mouse_scroll_offset = mouse_scroll_offset;
}

void keyboardCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
  if( action == GLFW_PRESS )
  {
    active_input->addInput( key );
    //active_input->notify( "KEY_PRESSED" );
  }
  else if( action == GLFW_RELEASE )
  {
    active_input->removeInput( key );
    //active_input->notify( "KEY_RELEASED" );
  }
}

void mouseScrollCallback( GLFWwindow* window, double xoffset, double yoffset )
{
  active_input->setMouseScroll( WMath::vec2( xoffset, yoffset ) );
  active_input->notify( "MOUSE_SCROLL" );
}

void mouseButtonCallback( GLFWwindow* window, int button, int action, int mods )
{
  if( action == GLFW_PRESS )
  {
    active_input->addInput( button );
  }
  else if( action == GLFW_RELEASE )
  {
    active_input->removeInput( button );
  }
}