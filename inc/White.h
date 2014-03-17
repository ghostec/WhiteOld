// White.h
// This is the main class for the Game Engine
// Given the wanted architecture (OSX, Linux, Windows, iOS, Android)
// it creates all the context to be used (Window, Input and Renderer)

#ifndef __WHITE_WHITE__
#define __WHITE_WHITE__

#include "Renderer/Window.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelFactory.h"
#include "Input/Input.h"

typedef enum _Architecture { OSX } Architecture;

class White
{
  private:
    void setArchitectureOSX();
    void setWindowOSX();
    void setInputOSX();
    void setRendererOSX();
    void setModelFactoryOSX();
    Window*WWindow;
    Input* WInput;
    Renderer* WRenderer;
    ModelFactory* WModelFactory;
  public:
    void setArchitecture( Architecture architecture );
    Window* getWindow() { return this->WWindow; }
    Input* getInput() { return this->WInput; }
    Renderer* getRenderer() { return this-> WRenderer; }
    ModelFactory* getModelFactory() { return this->WModelFactory; }
};

#endif
