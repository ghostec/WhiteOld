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

include_directories(${White_SOURCE_DIR}/WMath/inc/${White_SOURCE_DIR}/Renderer/inc)

SET(
  Renderer_SRCs
  Renderer.cpp
  ShaderFactory.cpp
  ShaderGLSL.cpp
  OpenGL/Model.cpp 
  ModelHelper.cpp
  Camera.cpp
  Scene.cpp
  Window.cpp
  GLFWhelper.cpp
)

SET( Renderer_Hs_DIR ../inc/Renderer )

SET(
  Renderer_Hs
  Camera.h
  GLFWhelper.h
  Model.h
  ModelHelper.h
  OpenGL/Model.h
  Renderer.h
  Scene.h
  Shader.h
  ShaderFactory.h
  ShaderGLSL.h
  Window.h
)

FOREACH(Renderer_H ${Renderer_Hs})
  LIST(APPEND Renderer_Hs_PATHs "${Renderer_Hs_DIR}/${Renderer_H}")
ENDFOREACH() 

add_library( Renderer ${Renderer_SRCs} ${Renderer_Hs_PATHs} )

target_link_libraries(Renderer ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${GLFW_LIBRARY} WMath)