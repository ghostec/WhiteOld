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
    void addFloat( std::string name, float f ) { d_float[name] = f; }
    void addMat4( std::string name, WMath::mat4 m ) { d_mat4[name] = m; }
    float* getFloat( std::string name ) { return &d_float[name]; }
    WMath::mat4* getMat4( std::string name ) { return &d_mat4[name]; }
    std::map< std::string, float >* getFloatMap() { return &d_float; }
    std::map< std::string, WMath::mat4 >* getMat4Map( ) { return &d_mat4; }
};

#endif
