#include "WMath/interpolation.h"

namespace WMath
{
  float linear_interpolation( float x, float duration,
                              float initial_value, float final_value )
  {
    return ( ( final_value - initial_value ) / duration ) * x + initial_value;
  }
}
