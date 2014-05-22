#ifndef __WHITE_GLFWINPUT__
#define __WHITE_GLFWINPUT__

#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Window.h"
#include "Helpers/Observable.h"
#include <string>
#include <thread>
#include <chrono>

#define Key int

class Input : public Observable<std::string>
{
  private:
    GLFWwindow* window;
  public:
    Input( GLFWwindow* window );
    bool isKeyPressed( Key key );
    void getMousePos( int* x, int* y );
};

extern Input* active_input;

void keyboardCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
void mouseButtonCallback( GLFWwindow* window, int button, int action, int mods );

#endif
