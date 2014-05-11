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
}

void White::setWindowOSX()
{
  this->WWindow = new Window();
}

void White::setInputOSX()
{
  this->WInput = new Input( this->WWindow->getWindow() );
}

void White::setRendererOSX()
{
  RendererContext rc;
  rc.window = this->WWindow;
  rc.input = this->WInput;
  WRenderer = new Renderer( rc );
}
