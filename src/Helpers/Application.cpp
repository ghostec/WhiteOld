#include "Helpers/Application.h"

namespace ApplicationHelper
{

  std::string ReadFile(const std::string file_path)
  {
    std::ifstream File( file_path.c_str() );

    // find the file size
    File.seekg(0,std::ios::end);
    std::streampos length = File.tellg();
    File.seekg(0,std::ios::beg);

    // read whole file into a vector:
    std::vector<char> buffer(length);
    File.read(&buffer[0],length);

    // return the shader string
    return std::string( buffer.begin(), buffer.end() );
  }

}
