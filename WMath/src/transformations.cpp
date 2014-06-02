#include "WMath/transformations.h"

namespace WMath
{
  void translate( std::shared_ptr<mat4> t_matrix, vec3 v )
  {
    mat4 m;
    m[0][3] = v[0];
    m[1][3] = v[1];
    m[2][3] = v[2];
    (*t_matrix) = (*t_matrix) * m;
  }

  void scale( std::shared_ptr<mat4> t_matrix, vec3 v )
  {
    mat4 m;
    m[0][0] = v[0];
    m[1][1] = v[1];
    m[2][2] = v[2];
    m[3][3] = 1.0f;
    (*t_matrix) = (*t_matrix) * m;
  }

  void rotate_x( std::shared_ptr<mat4> t_matrix, float degrees )
  {
    mat4 m;
    m[1][1] = cos( degrees * PI / 180.0 );
    m[1][2] = -sin( degrees * PI / 180.0 );
    m[2][1] = sin( degrees * PI / 180.0 );
    m[2][2] = cos( degrees * PI / 180.0 );
    ( *t_matrix ) = ( *t_matrix ) * m;
  }

  void rotate_y( std::shared_ptr<mat4> t_matrix, float degrees )
  {
    mat4 m;
    m[0][0] = cos(degrees * PI / 180.0);
    m[0][2] = -sin(degrees * PI / 180.0);
    m[2][0] = sin(degrees * PI / 180.0);
    m[2][2] = cos(degrees * PI / 180.0);
    (*t_matrix) = (*t_matrix) * m;
  }

  void rotate_z( std::shared_ptr<mat4> t_matrix, float degrees )
  {
    mat4 m;
    m[0][0] = cos( degrees * PI / 180.0 );
    m[0][1] = -sin( degrees * PI / 180.0 );
    m[1][0] = sin( degrees * PI / 180.0 );
    m[1][1] = cos( degrees * PI / 180.0 );
    ( *t_matrix ) = ( *t_matrix ) * m;
  }
}