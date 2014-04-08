project(WMath)
include_directories(${White_SOURCE_DIR}/WMath/inc)

SET(
  WMath_SRCs
  mat4.cpp
  vec4.cpp
  vec3.cpp
  transformations.cpp
)

SET( WMath_Hs_DIR ../inc/WMath )

SET(
  WMath_Hs
  WMath.h
  transformations.h
)

FOREACH(WMath_H ${WMath_Hs})
  LIST(APPEND WMath_Hs_PATHs "${WMath_Hs_DIR}/${WMath_H}")
ENDFOREACH()

add_library(WMath ${WMath_SRCs} ${WMath_Hs_PATHs})