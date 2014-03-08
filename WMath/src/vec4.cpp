#include "WMath/WMath.h"
#include <cmath>

namespace WMath
{
  vec4::vec4()
  {
    vec[0] = vec[1] = vec[2] = vec[3] = 0.0f;
  }

  vec4::vec4( float a )
  {
    vec[0] = vec[1] = vec[2] = vec[3] = a;
  }

  vec4::vec4( float x, float y, float z, float w )
  {
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
    vec[3] = w;
  }

  vec4::vec4( vec3 v, float w )
  {
    vec[0] = v[0];
    vec[1] = v[1];
    vec[2] = v[2];
    vec[3] = w;
  }

  vec4::vec4( float x, vec3 v )
  {
    vec[0] = x;
    vec[1] = v[1];
    vec[2] = v[2];
    vec[3] = v[3];
  }

  const float& vec4::operator[] ( int index ) const
  {
    return this->vec[index];
  }
  float& vec4::operator[] ( int index )
  {
    return this->vec[index];
  }

  float dot( vec4 v1, vec4 v2 )
  {
    return ( v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3] );
  }

  vec4 normalize( vec4 v )
  {
    float norm = 0.0f;
    norm = sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3] );
    std::cout << norm << std::endl;
    v[0] = v[0] / norm;
    v[1] = v[1] / norm;
    v[2] = v[2] / norm;
    v[3] = v[3] / norm;
    return v;
  }
}
