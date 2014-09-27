#ifndef __WHITE_GLFWINPUT__
#define __WHITE_GLFWINPUT__

#include <string>
#include <thread>
#include <chrono>
#include <set>
#include "Renderer/Helpers/GLFW.h"
#include "Renderer/Window.h"
#include "Helpers/Observable.h"
#include "WMath/WMath.h"

template<typename T>
bool isSubset( std::set<T> subset, std::set<T> set );

typedef enum _InputState
{
  PRESS, RELEASE, HOLD
} InputState;

class Input : public Observable<std::string>
{
  private:
    GLFWwindow* window;
    std::set<int> input;
    WMath::vec2 mouse_scroll_offset;
  public:
    Input( GLFWwindow* window );
    bool isKeyPressed( int Key );
    WMath::vec2 getMousePos();
    void setMouseScroll( WMath::vec2 mouse_scroll_offset );
    const WMath::vec2 getMouseScroll() { return this->mouse_scroll_offset; }
    void addInput( int i ) { this->input.insert( i ); }
    void removeInput( int i ) { this->input.erase( i ); }
    bool hasInput( std::set<int> input, InputState state );
    std::set<int> getInput() { return this->input; }
};

extern Input* active_input;

void intboardCallback( GLFWwindow* window, int Key, int scancode, int action, int mods );
void mouseScrollCallback( GLFWwindow* window, double xoffset, double yoffset );
void mouseButtonCallback( GLFWwindow* window, int button, int action, int mods );

#endif
