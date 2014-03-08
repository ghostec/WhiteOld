#include "WMath/WMath.h"

namespace WMath
{

  mat4::mat4()
  {
    columns[0] = vec4( 1.0f, 0.0f, 0.0f, 0.0f );
    columns[1] = vec4( 0.0f, 1.0f, 0.0f, 0.0f );
    columns[2] = vec4( 0.0f, 0.0f, 1.0f, 0.0f );
    columns[3] = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
  }

  mat4::mat4( vec4 x, vec4 y, vec4 z, vec4 w )
  {
    columns[0] = x;
    columns[1] = y;
    columns[2] = z;
    columns[3] = w;
  }

  const vec4& mat4::operator[]( int index ) const
  {
    return columns[index];
  }
  vec4& mat4::operator[]( int index )
  {
    return columns[index];
  }

  vec4 operator*( const mat4& m, const vec4& v )
  {
    return vec4(
        m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
        m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
        m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
        m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]
        );
  }

  vec4 operator*( const vec4& v, const mat4& m )
  {
    return vec4(
        v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2] + v[3] * m[0][3],
        v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2] + v[3] * m[1][3],
        v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2] + v[3] * m[2][3],
        v[0] * m[3][0] + v[1] * m[3][1] + v[2] * m[3][2] + v[3] * m[3][3]
        );
  }

  mat4 operator*( const mat4& m1, const mat4& m2 )
  {
    vec4 X = m1 * m2[0];
    vec4 Y = m1 * m2[1];
    vec4 Z = m1 * m2[2];
    vec4 W = m1 * m2[3];

    return mat4( X, Y, Z, W );
  }

  mat4 translate( vec3 vector )
  {
    mat4 m;
    m[0][3] = vector[0];
    m[1][3] = vector[1];
    m[2][3] = vector[2];
    return m;
  }

  mat4 scale( vec3 vector )
  {
    mat4 m;
    m[0][0] = vector[0];
    m[1][1] = vector[1];
    m[2][2] = vector[2];
    m[3][3] = 1.0f;
    return m;
  }

  mat4 rotate_x( float degree )
  {
    mat4 m;
    m[1][1] = cos( degree * PI / 180.0 );
    m[1][2] = - sin( degree * PI / 180.0 );
    m[2][1] = sin( degree * PI / 180.0 );
    m[2][2] = cos( degree * PI / 180.0 );
    return m;
  }

  mat4 rotate_z( float degree )
  {
    mat4 m;
    m[0][0] = cos( degree * PI / 180.0 );
    m[0][1] = - sin( degree * PI / 180.0 );
    m[1][0] = sin( degree * PI / 180.0 );
    m[1][1] = cos( degree * PI / 180.0 );
    return m;
  }

  float* value_ptr( mat4 *m )
  {
    return &m->columns[0][0];
  }

}
