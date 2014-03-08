#include "WMath/WMath.h"
#include <cmath>

namespace WMath
{
  vec3::vec3()
  {
    vec[0] = vec[1] = vec[2] = 0.0f;
  }

  vec3::vec3( float a );
  {
    vec[0] = vec[1] = vec[2] = a;
  }

  vec3::vec3( float x, float y, float z )
  {
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
  }

  const float& vec3::operator[] ( int index ) const
  {
    return this->vec[index];
  }
  float& vec3::operator[] ( int index )
  {
    return this->vec[index];
  }

  float dot( vec3 v1, vec3 v2 )
  {
    return ( v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] );
  }

  vec3 normalize( vec3 v )
  {
    float norm = 0.0f;
    norm = sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
    std::cout << norm << std::endl;
    v[0] = v[0] / norm;
    v[1] = v[1] / norm;
    v[2] = v[2] / norm;
    return v;
  }
}
