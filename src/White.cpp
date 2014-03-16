#include "White.h"

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
  setCameraFactoryOSX();
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

void White::setCameraFactoryOSX()
{
  this->WCameraFactory = new CameraFactoryOpenGL();
}
