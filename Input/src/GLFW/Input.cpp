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

void Input::addInput( int i, InputState state )
{
  if( state == PRESS ) this->press.insert( i );
  else this->hold.insert( i );
}

void Input::removeInput( int i, InputState state )
{
  if( state == PRESS ) this->press.erase( i );
  else this->hold.erase( i );
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
  std::set<int>* set;
  if( state == PRESS ) set = &this->press;
  else set = &this->hold;

  if( isSubset<int>( input, *set ) )
  {
    if( state == PRESS ) for( int i : input ) this->press.erase( i );
    return true;
  }
  else return false;
}


void keyboardCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
  if( action == GLFW_PRESS )
  {
    active_input->addInput( key, HOLD );
  }
  else if( action == GLFW_RELEASE )
  {
    active_input->addInput( key, PRESS );
    active_input->removeInput( key, HOLD );
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
    active_input->addInput( button, HOLD );
  }
  else if( action == GLFW_RELEASE )
  {
    active_input->addInput( button, PRESS );
    active_input->removeInput( button, HOLD );
  }
}