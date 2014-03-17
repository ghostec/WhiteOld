#ifndef __WHITE_SHADER__
#define __WHITE_SHADER__

#include <iostream>
#include <string>

class Shader
{
  public:
    virtual void before_draw() = 0;
    virtual void after_draw() = 0;
};

#endif
