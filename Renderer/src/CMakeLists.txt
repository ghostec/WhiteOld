project(Renderer)

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

include_directories(${White_SOURCE_DIR}/WMath/inc/ ${White_SOURCE_DIR}/Renderer/inc)
add_library(Renderer Renderer.cpp ModelFactory.cpp ModelOpenGL.cpp ModelHelper.cpp CameraFactory.cpp CameraOpenGL.cpp Scene.cpp Window.cpp GLFWhelper.cpp)

target_link_libraries(Renderer ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${GLFW_LIBRARY} WMath)
