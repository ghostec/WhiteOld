cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

project(White)

add_definitions(-DOPENGL)

subdirs(WMath Input Renderer Physics tinyxml2)

include_directories( ${White_SOURCE_DIR} ${White_SOURCE_DIR}/inc
  ${White_SOURCE_DIR}/Input/inc ${White_SOURCE_DIR}/WMath/inc
  ${White_SOURCE_DIR}/Renderer/inc ${White_SOURCE_DIR}/Physics/inc )

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

SET( Hs_DIR inc )

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

target_link_libraries( White tinyxml2 Input WMath Renderer Physics )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})