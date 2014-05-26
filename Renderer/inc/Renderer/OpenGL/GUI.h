#ifndef __RENDERER_GUIOPENGL__
#define __RENDERER_GUIOPENGL__

#include <vector>
#include <array>
#include <GL/glew.h>
#include "WMath/WMath.h"

class GUI
{
  public:
    std::vector< WMath::vec3 > vertices;
    std::vector< WMath::vec3 > uvs;
    std::vector< WMath::vec3 > normals;
    std::vector< std::array< GLushort, 3 > > elements;
    GUI( float offset_x, float offset_y, float ar, float percent );
};

#endif
