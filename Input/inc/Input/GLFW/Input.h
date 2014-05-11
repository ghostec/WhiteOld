#ifndef __WHITE_GLFWINPUT__
#define __WHITE_GLFWINPUT__

#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Window.h"

#define Key int

typedef struct _GLFWcontext
{
  Window *window;
} GLFWcontext;

class Input
{
  private:
    GLFWcontext context;
    void setWindow( Window *window );
  public:
    Input( GLFWcontext context );
    bool isKeyPressed( Key key );
};

#endif
