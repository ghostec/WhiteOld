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

SET(
  OpenGL_SRCs
  OpenGL/ModelAsset.cpp 
  OpenGL/Shader.cpp
  OpenGL/Renderer.cpp
  OpenGL/MousePicking.cpp
)

SET(
  OpenGL_Hs
  OpenGL/ModelAsset.h
  OpenGL/Shader.h
  OpenGL/Renderer.h
  OpenGL/MousePicking.h
)

SET(
  Helpers_SRCs
  Helpers/ModelAssetHelper.cpp
  Helpers/GLFW.cpp
)

SET(
  Helpers_Hs
  Helpers/ModelAssetHelper.h
  Helpers/GLFW.h
)

SET(
  Renderer_SRCs
  Camera.cpp
  Scene.cpp
  Light.cpp
  Window.cpp
  ModelInstance.cpp
  ${Helpers_SRCs}
  ${OpenGL_SRCs}
)

SET( Renderer_Hs_DIR  ../inc/Renderer )

SET(
  Renderer_Hs
  Camera.h
  ModelAsset.h
  Renderer.h
  Scene.h
  Light.h
  Shader.h
  Window.h
  ModelInstance.h
  MousePicking.h
  ${Helpers_Hs}
  ${OpenGL_Hs}
)

FOREACH(OpenGL_H ${OpenGL_Hs})
  LIST(APPEND OpenGL_Hs_PATHs "${Renderer_Hs_DIR}/${OpenGL_H}")
ENDFOREACH()

FOREACH(Helper_H ${Helpers_Hs})
  LIST(APPEND Helpers_Hs_PATHs "${Renderer_Hs_DIR}/${Helper_H}")
ENDFOREACH()

FOREACH(Renderer_H ${Renderer_Hs})
  LIST(APPEND Renderer_Hs_PATHs "${Renderer_Hs_DIR}/${Renderer_H}")
ENDFOREACH() 

add_library( Renderer ${Renderer_SRCs} ${Renderer_Hs_PATHs} )

target_link_libraries(Renderer ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${White_SOURCE_DIR}/Renderer/src/SOIL/SOIL.lib WMath)

source_group("Source Files\\Helpers" FILES ${Helpers_SRCs})
source_group("Header Files\\Helpers" FILES ${Helpers_Hs_PATHs})

source_group("Source Files\\OpenGL" FILES ${OpenGL_SRCs})
source_group("Header Files\\OpenGL" FILES ${OpenGL_Hs_PATHs})