#ifndef __WHITE_INPUT__
#define __WHITE_INPUT__

#include "GLFWhelper.h"
#include "Window.h"

#define Key int

typedef struct _InputContext
{
  Window *window;
} InputContext;

class Input
{
  private:
    InputContext context;
  public:
    Input( InputContext ic );
    void setWindow( Window *window );
    bool isKeyPressed( Key key );
};

Input::Input( InputContext ic )
{
  this->setWindow( ic.window );
}

void Input::setWindow( Window *window )
{
  this->context.window = window;
}

bool Input::isKeyPressed( Key key )
{
  return GLFWhelper::isKeyPressed( this->context.window->getWindow(), key );
}

#endif
