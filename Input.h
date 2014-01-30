#ifndef __WHITE_INPUT__
#define __WHITE_INPUT__

#include "GLFWhelper.h"
#include "Window.h"

#define Key int

class Input
{
  public:
    virtual bool isKeyPressed ( Key key ) = 0;
};

typedef struct _GLFWcontext
{
  Window *window;
} GLFWcontext;

class InputGLFW : public Input
{
  private:
    GLFWcontext context;
    void setWindow( Window *window );
  public:
    InputGLFW( GLFWcontext context );
    bool isKeyPressed( Key key );
};


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

#endif
