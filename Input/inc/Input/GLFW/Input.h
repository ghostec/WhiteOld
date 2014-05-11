#ifndef __WHITE_GLFWINPUT__
#define __WHITE_GLFWINPUT__

#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Window.h"
#include "Helpers/Observable.h"
#include <string>

#define Key int

typedef struct _GLFWcontext
{
  Window *window;
} GLFWcontext;

class Input : public Observable<std::string>
{
  private:
    GLFWcontext context;
    void setWindow( Window *window );
  public:
    Input( GLFWcontext context );
    bool isKeyPressed( Key key );
};

#endif
