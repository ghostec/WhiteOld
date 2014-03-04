cmake_minimum_required (VERSION 2.8)

project(White)

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

include_directories(${White_SOURCE_DIR}/WMath/inc)

add_executable(White main.cpp ApplicationHelper.cpp)

target_link_libraries(White ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${GLFW_LIBRARY} Input WMath Renderer)
