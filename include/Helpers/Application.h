#ifndef __WHITE_APPLICATIONHELPER__
#define __WHITE_APPLICATIONHELPER__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <vector>

namespace ApplicationHelper
{
  int ReadFile( const std::string file_path, std::string* content );
}

#endif
