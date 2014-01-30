#ifndef __WHITE_INPUT__
#define __WHITE_INPUT__

#include "GLFWhelper.h"
#include "Window.h"

#define Key int

class Input
{
  private:
    Window *window;
  public:
    void setWindow( Window *window );
    bool isKeyPressed( Key key );
};

void Input::setWindow( Window *window )
{
  this->window = window;
}

bool Input::isKeyPressed( Key key )
{
  return GLFWhelper::isKeyPressed( this->window->getWindow(), key );
}

#endif
