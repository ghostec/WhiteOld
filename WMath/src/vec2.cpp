#include "WMath/WMath.h"
#include <cmath>

namespace WMath
{
  vec2::vec2()
  {
    vec[0] = vec[1] = 0.0f;
  }

  vec2::vec2( float a )
  {
    vec[0] = vec[1] = a;
  }

  vec2::vec2( float x, float y )
  {
    vec[0] = x;
    vec[1] = y;
  }

  const float& vec2::operator[] ( int index ) const
  {
    return this->vec[index];
  }
  float& vec2::operator[] ( int index )
  {
    return this->vec[index];
  }

  vec2 operator*( const float& f, const vec2& v )
  {
    return vec2( f * v[0], f * v[1] );
  }
  vec2 operator*( const vec2& v, const float& f )
  {
    return vec2( f * v[0], f * v[1] );
  }
  vec2 operator+( const vec2& v1, const vec2& v2 )
  {
    return vec2( v1[0] - v2[0], v1[1] - v2[1] );
  }
  vec2 operator-( const vec2& v1, const vec2& v2 )
  {
    return vec2( v1[0] + v2[0], v1[1] + v2[1] );
  }

  float dot( vec2 v1, vec2 v2 )
  {
    return ( v1[0] * v2[0] + v1[1] * v2[1] );
  }
}
