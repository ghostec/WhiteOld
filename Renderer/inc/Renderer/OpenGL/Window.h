#ifndef __RENDERER_OPENGLWINDOW__
#define __RENDERER_OPENGLWINDOW__

#include <string>
#include "Renderer/Helpers/GLFW.h"
#include "WMath/WMath.h"
#include "Helpers/Observable.h"

class Window : public Observable<std::string>
{
private:
  GLFWwindow* window;
  WMath::vec2 dimensions;
  bool dirty;
public:
  Window( WMath::vec2 dimensions );
  bool isOpen();
  void setDimensions( WMath::vec2 d );
  void setDirty( bool v ) { this->dirty = v; }
  GLFWwindow *getWindow() { return this->window; }
  WMath::vec2 getDimensions() { return this->dimensions; }
  bool getDirty() { return this->dirty; }
};

extern Window* active_window;

#endif
