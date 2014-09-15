cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

project(White)

add_definitions(-DOPENGL)

subdirs(WMath Input Renderer tinyxml2)

include_directories( ${White_SOURCE_DIR} ${White_SOURCE_DIR}/inc
  ${White_SOURCE_DIR}/Input/inc ${White_SOURCE_DIR}/WMath/inc
  ${White_SOURCE_DIR}/Renderer/inc ${White_SOURCE_DIR}/bullet3-master/src )

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

find_library(BULLET_DYNAMICS_LIBRARY
    NAMES BulletDynamics
    HINTS "${White_SOURCE_DIR}/bullet3-master/build/lib/Release"
	REQUIRED
)

find_library(BULLET_COLLISION_LIBRARY
    NAMES BulletCollision
    HINTS "${White_SOURCE_DIR}/bullet3-master/build/lib/Release"
	REQUIRED
)

find_library(LINEAR_MATH_LIBRARY
    NAMES LinearMath
    HINTS "${White_SOURCE_DIR}/bullet3-master/build/lib/Release"
	REQUIRED
)

target_link_libraries( White tinyxml2 Input WMath Renderer
  ${BULLET_DYNAMICS_LIBRARY} ${BULLET_COLLISION_LIBRARY} ${LINEAR_MATH_LIBRARY} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})