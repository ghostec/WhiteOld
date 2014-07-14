#include "Helpers/Application.h"

namespace ApplicationHelper
{

  int ReadFile( const std::string file_path, std::string* content )
  {
    std::ifstream File( file_path.c_str() );

    if( !File.is_open() )
    {
      std::cout << file_path << std::endl;
      std::cout << "Error reading file" << std::endl;
      return -1;
    }

    // find the file size
    File.seekg(0,std::ios::end);
    std::streampos length = File.tellg();
    File.seekg(0,std::ios::beg);

    // read whole file into a vector:
    std::vector<char> buffer(length);
    File.read(&buffer[0],length);

    // return the shader string
    *content = std::string( buffer.begin(), buffer.end() );

    return 0;
  }

}
