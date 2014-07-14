#ifndef __WHITE_GLFWINPUT__
#define __WHITE_GLFWINPUT__

#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Window.h"
#include "Helpers/Observable.h"
#include <string>
#include <thread>
#include <chrono>
#include <set>

#define Key int

class Input : public Observable<std::string>
{
  private:
    GLFWwindow* window;
    std::set<int> keys;
  public:
    Input( GLFWwindow* window );
    bool isKeyPressed( Key key );
    void getMousePos( int* x, int* y );
    void addKey( int key ) { this->keys.insert( key ); }
    void removeKey( int key ) { this->keys.erase( key ); }
    const std::set<int> getKeys() { return this->keys; }
};

extern Input* active_input;

void keyboardCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
void mouseButtonCallback( GLFWwindow* window, int button, int action, int mods );

#endif
