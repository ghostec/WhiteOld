#include "WMath/WMath.h"
#include <cmath>

namespace WMath
{
  quaternion::quaternion()
  {
    vec[0] = vec[1] = vec[2] = vec[3] = 0.0f;
  }

  quaternion::quaternion( float x, float y, float z, float w )
  {
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
    vec[3] = w;
  }

  quaternion::quaternion( vec3 v, float w )
  {
    vec[0] = v[0];
    vec[1] = v[1];
    vec[2] = v[2];
    vec[3] = w;
  }

  const float& quaternion::operator[] ( int index ) const
  {
    return this->vec[index];
  }
  float& quaternion::operator[] ( int index )
  {
    return this->vec[index];
  }

  quaternion operator*( const quaternion& q1, const quaternion& q2 )
  {
    quaternion q3;
    q3[0] = q1[1] * q2[2] - q1[2] * q2[1] + q1[0] * q2[3] + q1[3] * q2[0];
    q3[1] = q1[2] * q2[0] - q1[0] * q2[2] + q1[1] * q2[3] + q1[3] * q2[1];
    q3[2] = q1[0] * q2[1] - q1[1] * q2[0] + q1[2] * q2[3] + q1[3] * q2[2];
    q3[3] = q1[3] * q2[3] - q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2];
    return q3;
  }

  quaternion normalize( quaternion v )
  {
    float norm = 0.0f;
    norm = sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3] );
    v[0] = v[0] / norm;
    v[1] = v[1] / norm;
    v[2] = v[2] / norm;
    v[3] = v[3] / norm;
    return v;
  }
}
