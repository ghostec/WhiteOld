#ifndef __WHITE_INPUT__
#define __WHITE_INPUT__

#include "Renderer/GLFWhelper.h"
#include "Renderer/Window.h"

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

#endif
