#ifndef __WHITE_GLFWINPUT__
#define __WHITE_GLFWINPUT__

#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Window.h"
#include "Helpers/Observable.h"
#include <string>

#define Key int

class Input : public Observable<std::string>
{
  private:
    GLFWwindow* window;
  public:
    Input( GLFWwindow* window );
    bool isKeyPressed( Key key );
};

extern Input* active_input;

void keyboardCallback( GLFWwindow* window, int key, int scancode, int action, int mods );

#endif
