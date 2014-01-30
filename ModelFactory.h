#ifndef __WHITE_MODELFACTORY__
#define __WHITE_MODELFACTORY__

#include <iostream>
#include "Model.h"

class ModelFactory
{
  private:
  public:
    virtual Model* createModel() = 0;
};

class ModelFactoryOpenGL : public ModelFactory
{
  private:
  public:
    Model* createModel();
};

Model* ModelFactoryOpenGL::createModel()
{
  std::cout << "Placeholder ModelFactoryOpenGL::createModel()" << std::endl;
  return new ModelOpenGL();
}

#endif
