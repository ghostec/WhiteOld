#ifndef __WHITE_APPLICATIONHELPER__
#define __WHITE_APPLICATIONHELPER__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <functional>

namespace ApplicationHelper
{
  int ReadFile( const std::string file_path, std::string* content );

  struct Job
  {
    void* object;
    void* method;
    std::function<void()> function;
  };

  class JobDispatcher
  {
    private:
      std::vector< std::function<void()> > jobs;
    public:
      void execute();
      void addJob( std::function<void()> job );
  };

  extern JobDispatcher* g_job_dispatcher;
}

void testss( std::string t );

#endif
