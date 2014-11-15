#ifndef __WHITE_WMATH_TRANSFORMATIONS__
#define __WHITE_WMATH_TRANSFORMATIONS__

#include <memory>
#include "WMath/WMath.h"

namespace WMath
{
  void setOrigin( mat4* t_matrix, vec3 v );
  void translate( mat4* t_matrix, vec3 v );
  void scale( mat4* t_matrix, vec3 v );
  void rotate_x( mat4* t_matrix, float degrees );
  void rotate_y( mat4* t_matrix, float degrees );
  void rotate_z( mat4* t_matrix, float degrees );
  void rotate( mat4* t_matrix, quaternion q );
  mat4 translateM( vec3 v );
  mat4 scaleM( vec3 v );
  mat4 rotateM( quaternion q );
}

#endif