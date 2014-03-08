#ifndef __WHITE_WMATH__
#define __WHITE_WMATH__

#include <iostream>
#include <cmath>

#define PI 3.14159265

namespace WMath
{
  class mat4
  {
    public:
      float mat[4][4];
      mat4();
      mat4 operator*(mat4 m1);
  };

  class vec3
  {
    public:
      float x, y, z;
      vec3();
      vec3( float a );
      vec3( float x, float y, float z );
      const float& operator[] ( int index ) const;
      float& operator[] ( int index );
 };

  class vec4
  {
    public:
      float vec[4];
      vec4();
      vec4( float a );
      vec4( float x, float y, float z, float w );
      vec4( vec3 v, float w );
      vec4( float x, vec3 v );
      const float& operator[] ( int index ) const;
      float& operator[] ( int index );
  };

  mat4 translate( vec3 vector );
  mat4 scale( vec3 vector );
  mat4 rotate_x( float degree );
  mat4 rotate_z( float degree );

  float dot( vec4 v1, vec4 v2 );
  vec4 normalize( vec4 v );

  float dot( vec3 v1, vec3 v2 );
  vec3 normalize( vec3 v );

  float* value_ptr( mat4 *m );
}
#endif
