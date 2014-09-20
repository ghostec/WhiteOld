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
  Physics_SRCs
  PhysicsManager.cpp
  Body.cpp
)

SET(
  Physics_Hs
  PhysicsManager.h
  Body.h
)

SET( Physics_Hs_DIR  ../inc/Physics )

FOREACH(Physics_H ${Physics_Hs})
  LIST(APPEND Physics_Hs_PATHs "${Physics_Hs_DIR}/${Physics_H}")
ENDFOREACH() 

add_library( Physics ${Physics_SRCs} ${Physics_Hs_PATHs} )

target_link_libraries(Physics ${BULLET_DYNAMICS_LIBRARY}
  ${BULLET_COLLISION_LIBRARY} ${LINEAR_MATH_LIBRARY} Renderer)