#ifndef __WHITE_MODELFACTORY__
#define __WHITE_MODELFACTORY__

#include <iostream>
#include "Renderer/Model.h"
#include "Renderer/ModelOpenGL.h"

class ModelFactory
{
  private:
  public:
    virtual Model* createModel( ModelFileType model_file_type,
                                std::string file_path ) = 0;
};

class ModelFactoryOpenGL : public ModelFactory
{
  private:
  public:
    Model* createModel( ModelFileType model_file_type,
                        std::string file_path );
};

#endif
