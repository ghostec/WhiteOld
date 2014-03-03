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
      vec3( float x = 0.0, float y = 0.0, float z = 0.0 );
  };

  mat4 translate( vec3 vector );
  mat4 scale( vec3 vector );
  mat4 rotate_x( float degree );

  float* value_ptr( mat4 *m );
}
#endif
