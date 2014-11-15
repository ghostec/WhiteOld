SET(
  Input_SRCs
  GLFW/Input.cpp
)

SET(
  Input_Hs
  Input.h
  GLFW/Input.h
)

SET( Input_Hs_DIR ../include/Input )

FOREACH(Input_H ${Input_Hs})
  LIST(APPEND Input_Hs_PATHs "${Input_Hs_DIR}/${Input_H}")
ENDFOREACH()

add_library(Input ${Input_SRCs} ${Input_Hs_PATHs})

source_group("Source Files\\GLFW" FILES GLFW/Input.cpp)
source_group("Header Files\\GLFW" FILES ../inc/Input/GLFW/Input.h)