project(Physics)

include_directories(${White_SOURCE_DIR}/bullet3-master/src ${White_SOURCE_DIR}/Physics/inc/ )

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

SET(
  Helpers_SRCs
  Helpers/XMLPhysics.cpp
)

SET(
  Helpers_Hs
  Helpers/XMLPhysics.h
)

SET(
  Physics_SRCs
  PhysicsManager.cpp
  Body.cpp
  ${Helpers_SRCs}
)

SET(
  Physics_Hs
  PhysicsManager.h
  Body.h
  ${Helpers_Hs}
)

SET( Physics_Hs_DIR  ../inc/Physics )

FOREACH(Helper_H ${Helpers_Hs})
  LIST(APPEND Helpers_Hs_PATHs "${Physics_Hs_DIR}/${Helper_H}")
ENDFOREACH()

FOREACH(Physics_H ${Physics_Hs})
  LIST(APPEND Physics_Hs_PATHs "${Physics_Hs_DIR}/${Physics_H}")
ENDFOREACH() 

add_library( Physics ${Physics_SRCs} ${Physics_Hs_PATHs} )

target_link_libraries(Physics ${BULLET_DYNAMICS_LIBRARY}
  ${BULLET_COLLISION_LIBRARY} ${LINEAR_MATH_LIBRARY} Renderer)

source_group("Source Files\\Helpers" FILES ${Helpers_SRCs})
source_group("Header Files\\Helpers" FILES ${Helpers_Hs_PATHs})