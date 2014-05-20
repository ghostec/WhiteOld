cmake_minimum_required (VERSION 2.8)

project(White)

add_definitions(-DOPENGL)

subdirs(WMath Input Renderer)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGl_DEFINITIONS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})

find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})
add_definitions(${GLFW_DEFINITIONS})

include_directories(${White_SOURCE_DIR}/inc)
include_directories(${White_SOURCE_DIR}/Input/inc)
include_directories(${White_SOURCE_DIR}/WMath/inc)
include_directories(${White_SOURCE_DIR}/Renderer/inc)

SET( SRCs_DIR src )

SET(
  Helpers_SRCs
  Helpers/Application.cpp
)

SET(
  Helpers_Hs
  Helpers/Application.h
  Helpers/Observable.h
)

SET(
  SRCs
  White.cpp
  ${Helpers_SRCs}
)

FOREACH(SRC ${SRCs})
  LIST(APPEND SRCs_PATHs "${SRCs_DIR}/${SRC}")
ENDFOREACH()

SET( Hs_DIR inc )

SET(
  Hs
  White.h
  ${Helpers_Hs}
)

FOREACH(H ${Hs})
  LIST(APPEND Hs_PATHs "${Hs_DIR}/${H}")
ENDFOREACH()

add_executable(White main.cpp ${SRCs_PATHs} ${Hs_PATHs})

source_group("Source Files\\Helpers" FILES ${Helpers_SRCs})
source_group("Header Files\\Helpers" FILES ${Helpers_Hs})

target_link_libraries(White ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${GLFW_LIBRARY} Input WMath Renderer)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})