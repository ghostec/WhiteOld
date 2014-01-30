#ifndef __WHITE_MODELFACTORY__
#define __WHITE_MODELFACTORY__

#include <iostream>
#include "Model.h"

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

Model* ModelFactoryOpenGL::createModel( ModelFileType model_file_type,
                                        std::string file_path )
{
  std::cout << "Placeholder ModelFactoryOpenGL::createModel()" << std::endl;
  return new ModelOpenGL( model_file_type, file_path );
}

#endif
