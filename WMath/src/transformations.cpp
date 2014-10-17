#include "WMath/transformations.h"

namespace WMath
{
  bool isPointInside
    ( WMath::vec2 anchor, WMath::vec2 dimensions, WMath::vec2 point )
  {
    if( point < anchor ) return false;
    if( point >= anchor && point <= (anchor + dimensions) ) return true;
  }

  void setOrigin( mat4* t_matrix, vec3 v )
  {
    mat4 m;
    m[0][3] = v[0];
    m[1][3] = v[1];
    m[2][3] = v[2];
    ( *t_matrix ) = m;
  }

  void translate( mat4* t_matrix, vec3 v )
  {
    mat4 m;
    m[0][3] = v[0];
    m[1][3] = v[1];
    m[2][3] = v[2];
    (*t_matrix) = (*t_matrix) * m;
  }

  void scale( mat4* t_matrix, vec3 v )
  {
    mat4 m;
    m[0][0] = v[0];
    m[1][1] = v[1];
    m[2][2] = v[2];
    m[3][3] = 1.0f;
    (*t_matrix) = (*t_matrix) * m;
  }

  void rotate_x( mat4* t_matrix, float degrees )
  {
    mat4 m;
    m[1][1] = cos( degrees * PI / 180.0 );
    m[1][2] = -sin( degrees * PI / 180.0 );
    m[2][1] = sin( degrees * PI / 180.0 );
    m[2][2] = cos( degrees * PI / 180.0 );
    ( *t_matrix ) = ( *t_matrix ) * m;
  }

  void rotate_y( mat4* t_matrix, float degrees )
  {
    mat4 m;
    m[0][0] = cos(degrees * PI / 180.0);
    m[0][2] = -sin(degrees * PI / 180.0);
    m[2][0] = sin(degrees * PI / 180.0);
    m[2][2] = cos(degrees * PI / 180.0);
    (*t_matrix) = (*t_matrix) * m;
  }

  void rotate_z( mat4* t_matrix, float degrees )
  {
    mat4 m;
    m[0][0] = cos( degrees * PI / 180.0 );
    m[0][1] = -sin( degrees * PI / 180.0 );
    m[1][0] = sin( degrees * PI / 180.0 );
    m[1][1] = cos( degrees * PI / 180.0 );
    ( *t_matrix ) = ( *t_matrix ) * m;
  }

  void rotate( mat4* t_matrix, quaternion q )
  {
    ( *t_matrix ) = rotateM( q );
  }

  mat4 translateM( vec3 v )
  {
    mat4 m;
    m[0][3] = v[0];
    m[1][3] = v[1];
    m[2][3] = v[2];
    return m;
  }

  mat4 scaleM( vec3 v )
  {
    mat4 m;
    m[0][0] = v[0];
    m[1][1] = v[1];
    m[2][2] = v[2];
    return m;
  }

  mat4 rotateM( quaternion qt )
  {
    mat4 m;
    quaternion q = normalize( qt );
    float vec[4] = { q.vec[0], q.vec[1], q.vec[2], q.vec[3] };
    m[0][0] = 1 - 2 * ( vec[1] * vec[1] + vec[2] * vec[2] );
    m[0][1] = 2 * ( vec[0] * vec[1] - vec[3] * vec[2] );
    m[0][2] = 2 * ( vec[0] * vec[2] + vec[3] * vec[1] );
    m[1][0] = 2 * ( vec[0] * vec[1] + vec[3] * vec[2] );
    m[1][1] = 1 - 2 * ( vec[0] * vec[0] + vec[2] * vec[2] );
    m[1][2] = 2 * ( vec[1] * vec[2] - vec[3] * vec[0] );
    m[2][0] = 2 * ( vec[0] * vec[2] - vec[3] * vec[1] );
    m[2][1] = 2 * ( vec[1] * vec[2] + vec[3] * vec[0] );
    m[2][2] = 1 - 2 * ( vec[0] * vec[0] + vec[1] * vec[1] );
    return m;
  }
}