#include <ModelFactory.h>

Model* ModelFactoryOpenGL::createModel( ModelFileType model_file_type,
                                        std::string file_path )
{
  std::cout << "Placeholder ModelFactoryOpenGL::createModel()" << std::endl;
  return new ModelOpenGL( model_file_type, file_path );
}
