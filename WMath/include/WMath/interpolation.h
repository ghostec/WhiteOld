#ifndef __WMATH_INTERPOLATION__
#define __WMATH_INTERPOLATION__

#include <iostream>
#include <cmath>
#include <chrono>

#define PI 3.14159265

namespace WMath
{
  float linear_interpolation( float x, float duration,
                              float initial_value, float final_value );
}

#endif
