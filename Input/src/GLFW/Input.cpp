#include "Input/GLFW/Input.h"

Input* active_input;

template<typename T>
bool isSubset( std::set<T> subset, std::set<T> set )
{
  for( typename std::set<T>::iterator it = subset.begin( ); it != subset.end( ); ++it )
  {
    bool e = false;
    for( int j = 0; j < set.size( ); j++ )
    {
      if( set.find( *it ) != set.end( ) )
      {
        e = true;
        break;
      }
    }
    if( e == false ) return false;
  }
  return true;
}

Input::Input( GLFWwindow* window )
{
  this->window = window;
}

bool Input::isKeyPressed( int Key )
{
  return GLFWhelper::isintPressed( this->window, Key );
}

void Input::addInput( int i )
{ 
  this->input.insert( i );
}

void Input::removeInput( int i )
{
  this->_press.erase( i );
  this->input.erase( i );
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

bool Input::hasInput( std::set<int> input, InputState state )
{
  // TODO: implement RELEASE
  if( isSubset<int>( input, this->input ) )
  {
    if( state == PRESS )
    {
      if( isSubset<int>( input, this->_press ) ) return false;
      else for( int i : input ) this->_press.insert( i );
    }
    return true;
  }
  else return false;
}


void keyboardCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
  if( action == GLFW_PRESS )
  {
    active_input->addInput( key );
  }
  else if( action == GLFW_RELEASE )
  {
    active_input->removeInput( key );
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