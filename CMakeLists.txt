cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

project(White)

find_library(TINYXML2_LIBRARY NAMES tinyxml2 PATHS tinyxml2/)

add_definitions(-DOPENGL)

subdirs(WMath Input Renderer Physics)

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
  ${Helpers_SRCs}
)

FOREACH(SRC ${SRCs})
  LIST(APPEND SRCs_PATHs "${SRCs_DIR}/${SRC}")
ENDFOREACH()

SET( Hs_DIR include )

SET(
  Hs
  ${Helpers_Hs}
)

FOREACH(H ${Hs})
  LIST(APPEND Hs_PATHs "${Hs_DIR}/${H}")
ENDFOREACH()

add_executable(White main.cpp ${SRCs_PATHs} ${Hs_PATHs})

source_group("Source Files\\Helpers" FILES ${Helpers_SRCs})
source_group("Header Files\\Helpers" FILES ${Helpers_Hs})

target_link_libraries( White Input WMath Renderer Physics ${TINYXML2_LIBRARY} )

include_directories( include tinyxml2 Renderer/include Physics/include Input/include WMath/include bullet3-master/src
Renderer/glew/include Renderer/glfw/include Renderer/freetype/include)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})