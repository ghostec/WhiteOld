#ifndef __WHITE_WMATH_TRANSFORMATIONS__
#define __WHITE_WMATH_TRANSFORMATIONS__

#include <memory>
#include "WMath/WMath.h"

namespace WMath
{
  void translate( std::shared_ptr<mat4> t_matrix, vec3 v );
  void scale( std::shared_ptr<mat4> t_matrix, vec3 v );
  void rotate_x( std::shared_ptr<mat4> t_matrix, float degrees );
  void rotate_y( std::shared_ptr<mat4> t_matrix, float degrees );
  void rotate_z( std::shared_ptr<mat4> t_matrix, float degrees );
}

#endif