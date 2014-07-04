#ifndef __RENDERER_MODELDATA__
#define __RENDERER_MODELDATA__

#include <map>
#include "WMath/WMath.h"

class ModelData
{
  private:
    std::map< std::string, float > d_float;
    std::map< std::string, WMath::mat4 > d_mat4;
  public:
    void addFloat( std::string name, float f ) { this->d_float[name] = f; }
    void addMat4( std::string name, WMath::mat4 m ) { this->d_mat4[name] = m; }
    float* getFloat( std::string name ) { return &this->d_float[name]; }
    WMath::mat4* getMat4( std::string name ) { return &this->d_mat4[name]; }
};

#endif
