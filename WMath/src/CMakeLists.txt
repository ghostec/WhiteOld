project(WMath)
include_directories(${White_SOURCE_DIR}/WMath/inc)

SET(
  WMath_SRCs
  mat4.cpp
  vec4.cpp
  vec3.cpp
  vec2.cpp
  quaternion.cpp
  transformations.cpp
  interpolation.cpp
)

SET( WMath_Hs_DIR ../include/WMath )

SET(
  WMath_Hs
  WMath.h
  transformations.h
  interpolation.h
)

FOREACH(WMath_H ${WMath_Hs})
  LIST(APPEND WMath_Hs_PATHs "${WMath_Hs_DIR}/${WMath_H}")
ENDFOREACH()

add_library(WMath ${WMath_SRCs} ${WMath_Hs_PATHs})