// White.h
// This is the main class for the Game Engine
// Given the wanted architecture (OSX, Linux, Windows, iOS, Android)
// it creates all the context to be used (Window, Input and Renderer)

#ifndef __WHITE_WHITE__
#define __WHITE_WHITE__

#include "Window.h"
#include "Input.h"
#include "Renderer.h"
#include "ModelFactory.h"

class Singleton
{
  private:
    Singleton() {}; // Constructor? (the {} brackets) are needed here.
    // Dont forget to declare these two. You want to make sure they
    // are unaccessable otherwise you may accidently get copies of
    // your singleton appearing.
    Singleton(Singleton const&);        // Don't Implement
    void operator=(Singleton const&);   // Don't implement
  public:
    static Singleton& getInstance()
    {
      static Singleton instance; 	// Guaranteed to be destroyed.
      // Instantiated on first use.
      return instance;
    }
};

typedef enum _Architecture { OSX } Architecture;

class White
{
  private:
    void setArchitectureOSX();
    void setWindowOSX();
    void setInputOSX();
    void setRendererOSX();
    void setModelFactoryOSX();
    Window *WWindow;
    Input *WInput;
    Renderer *WRenderer;
    ModelFactory *WModelFactory;
  public:
    void setArchitecture( Architecture architecture );
    Window* getWindow();
    Input* getInput();
    Renderer* getRenderer();
    ModelFactory* getModelFactory();
};

void White::setArchitecture( Architecture architecture )
{
  if( architecture == OSX ) setArchitectureOSX();
  else
    std::cout << "ERROR: Wrong Architecture" << std::endl;
}

void White::setArchitectureOSX()
{
  setWindowOSX();
  setInputOSX();
  setRendererOSX();
  setModelFactoryOSX();
}

void White::setWindowOSX()
{
  this->WWindow = new Window();
}

void White::setInputOSX()
{
  GLFWcontext glfwc;
  glfwc.window = this->WWindow;
  this->WInput = new InputGLFW( glfwc );
}

void White::setRendererOSX()
{
  RendererContext rc;
  rc.window = this->WWindow;
  rc.input = this->WInput;
  WRenderer = new Renderer( rc );
}

void White::setModelFactoryOSX()
{
  this->WModelFactory = new ModelFactoryOpenGL();
}

Window* White::getWindow()
{
  return this->WWindow;
}

Input* White::getInput()
{
  return this->WInput;
}

Renderer* White::getRenderer()
{
  return this->WRenderer;
}

ModelFactory* White::getModelFactory()
{
  return this->WModelFactory;
}

#endif
