#include "WMath/WMath.h"

namespace WMath
{

  mat4::mat4()
  {
    // column major
    // no arguments => Identity matrix
    for( int i=0; i<4; i++ )
      for( int j=0; j<4; j++ )
        mat[i][j] = 0.0f;

    mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = 1.0f;
  }

  mat4 translate( vec3 vector )
  {
    mat4 m;
    m.mat[0][3] = vector.x;
    m.mat[1][3] = vector.y;
    m.mat[2][3] = vector.z;
    return m;
  }

  mat4 scale( vec3 vector )
  {
    mat4 m;
    m.mat[0][0] = vector.x;
    m.mat[1][1] = vector.y;
    m.mat[2][2] = vector.z;
    return m;
  }

  mat4 rotate_x( float degree )
  {
    mat4 m;
    m.mat[1][1] = cos( degree * PI / 180.0 );
    m.mat[1][2] = - sin( degree * PI / 180.0 );
    m.mat[2][1] = sin( degree * PI / 180.0 );
    m.mat[2][2] = cos( degree * PI / 180.0 );
    return m;
  }

  mat4 rotate_z( float degree )
  {
    mat4 m;
    m.mat[0][0] = cos( degree * PI / 180.0 );
    m.mat[0][1] = - sin( degree * PI / 180.0 );
    m.mat[1][0] = sin( degree * PI / 180.0 );
    m.mat[1][1] = cos( degree * PI / 180.0 );
    return m;
  }

  mat4 mat4::operator*(mat4 m1)
  {
    mat4 m;
    for( int i=0; i<4; i++ )
    {
      for( int j=0; j<4; j++ )
      {
        float sum = 0.0;
        for( int k=0; k<4; k++ )
        {
          sum += this->mat[i][k] * m1.mat[k][j];
        }
        m.mat[i][j] = sum;
      }
    }
    return m;
  }

  float* value_ptr( mat4 *m )
  {
    return &m->mat[0][0];
  }

}
