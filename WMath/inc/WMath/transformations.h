#ifndef __WHITE_WMATH_TRANSFORMATIONS__
#define __WHITE_WMATH_TRANSFORMATIONS__

#include "WMath/WMath.h"

namespace WMath
{
  void translate( mat4* t_matrix, vec3 v );
  void scale( mat4* t_matrix, vec3 v );
  void rotate_x( mat4* t_matrix, float degrees );
  void rotate_y( mat4* t_matrix, float degrees );
  void rotate_z( mat4* t_matrix, float degrees );
}

#endif