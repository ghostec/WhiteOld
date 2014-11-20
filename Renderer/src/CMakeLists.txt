project(Renderer)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGl_DEFINITIONS})

find_library(GLEW_LIBRARY NAMES glew32 PATHS ../glew/lib/Release/Win32)
find_library(FREETYPE_LIBRARY NAMES freetype PATHS ../freetype/build/Release)
find_library(GLFW_LIBRARY NAMES glfw3 PATHS ../glfw/build/src/Release)

set(TINYXML2_INCLUDE_DIR ${WHITE_SOURCE_DIR}/tinyxml2)
set(GLEW_INCLUDE_DIRS ../glew/include)
set(GLFW_INCLUDE_DIRS ../glfw/include)
set(FREETYPE_INCLUDE_DIRS ../freetype/include)

set(WHITE_RENDERER_INCLUDE_DIRS ${White_SOURCE_DIR}/WMath/inc/ ../inc)

SET(
  OpenGL_SRCs
  OpenGL/Mesh.cpp
  OpenGL/Shader.cpp
  OpenGL/Renderer.cpp
  OpenGL/MousePicking.cpp
  OpenGL/Texture.cpp
  OpenGL/Window.cpp
  OpenGL/GUIText.cpp
  OpenGL/GUITextManager.cpp
)

SET(
  OpenGL_Hs
  OpenGL/Mesh.h
  OpenGL/Shader.h
  OpenGL/Renderer.h
  OpenGL/MousePicking.h
  OpenGL/Texture.h
  OpenGL/Window.h
  OpenGL/GUIText.h
  OpenGL/GUITextManager.h
)

SET(
  Helpers_SRCs
  Helpers/CameraHelper.cpp
  Helpers/MeshHelper.cpp
  Helpers/GLFW.cpp
  Helpers/XMLAssets.cpp
  Helpers/XMLScene.cpp
  Helpers/XMLGUIScene.cpp
)

SET(
  Helpers_Hs
  Helpers/CameraHelper.h
  Helpers/MeshHelper.h
  Helpers/GLFW.h
  Helpers/XMLAssets.h
  Helpers/XMLScene.h
  Helpers/XMLGUIScene.h
  Helpers/RendererHelper.h
  Helpers/ShaderHelper.h
)

SET(
  Helpers_OpenGL_SRCs
  Helpers/OpenGL/RendererHelper.cpp
  Helpers/OpenGL/ShaderHelper.cpp
)

SET(
  Helpers_OpenGL_Hs
  Helpers/OpenGL/RendererHelper.h
  Helpers/OpenGL/ShaderHelper.h
)

SET(
  Renderer_SRCs
  Camera.cpp
  Scene.cpp
  Light.cpp
  Model.cpp
  ModelData.cpp
  Vertex.cpp
  SceneEditor.cpp
  GUIManager.cpp
  GUIElement.cpp
  GUIScene.cpp
  Effect.cpp
  EffectsManager.cpp
  SceneGraph.cpp
  SGNode.cpp
  Viewport.cpp
  ${Helpers_SRCs}
  ${OpenGL_SRCs}
  ${Helpers_OpenGL_SRCs}
)

SET( Renderer_Hs_DIR  ../include/Renderer )

SET(
  Renderer_Hs
  Camera.h
  Mesh.h
  Renderer.h
  Scene.h
  Light.h
  Shader.h
  Window.h
  ModelData.h
  Model.h
  Vertex.h
  MousePicking.h
  SceneEditor.h
  GUIManager.h
  GUIElement.h
  GUIScene.h
  GUITextManager.h
  GUIText.h
  Effect.h
  EffectsManager.h
  ResourceManager.h
  Texture.h
  SceneGraph.h
  SGNode.h
  Containable.h
  Viewport.h
  ${Helpers_Hs}
  ${OpenGL_Hs}
  ${Helpers_OpenGL_Hs}
)

FOREACH(OpenGL_H ${OpenGL_Hs})
  LIST(APPEND OpenGL_Hs_PATHs "${Renderer_Hs_DIR}/${OpenGL_H}")
ENDFOREACH()

FOREACH(Helper_H ${Helpers_Hs})
  LIST(APPEND Helpers_Hs_PATHs "${Renderer_Hs_DIR}/${Helper_H}")
ENDFOREACH()

FOREACH(Helper_OpenGL_H ${Helpers_OpenGL_Hs})
  LIST(APPEND Helpers_OpenGL_Hs_PATHs "${Renderer_Hs_DIR}/${Helper_OpenGL_H}")
ENDFOREACH()

FOREACH(Renderer_H ${Renderer_Hs})
  LIST(APPEND Renderer_Hs_PATHs "${Renderer_Hs_DIR}/${Renderer_H}")
ENDFOREACH() 

add_library(Renderer ${Renderer_SRCs} ${Renderer_Hs_PATHs} )

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  SET( SOIL_LIB libSOIL.dylib )
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  SET( SOIL_LIB soil.lib )
endif()

target_link_libraries(Renderer WMath Input ${OPENGL_LIBRARIES}
  ${TINYXML2_LIBRARY} ${GLEW_LIBRARY}
  ${GLFW_LIBRARY} ${FREETYPE_LIBRARY}
  ${White_SOURCE_DIR}/Renderer/src/SOIL/${SOIL_LIB} WMath)

source_group("Source Files\\Helpers" FILES ${Helpers_SRCs})
source_group("Header Files\\Helpers" FILES ${Helpers_Hs_PATHs})

source_group("Source Files\\OpenGL" FILES ${OpenGL_SRCs})
source_group("Header Files\\OpenGL" FILES ${OpenGL_Hs_PATHs})

source_group("Source Files\\Helpers\\OpenGL" FILES ${Helpers_OpenGL_SRCs})
source_group("Header Files\\Helpers\\OpenGL" FILES ${Helpers_OpenGL_Hs_PATHs})
