#ifndef __PHYSICS_PHYSICSMANAGER__
#define __PHYSICS_PHYSICSEMANAGER__

#include <vector>
#include "btBulletDynamicsCommon.h"
#include "Physics/Body.h"

class PhysicsManager
{
  private:
    btBroadphaseInterface*                  broadphase;
    btDefaultCollisionConfiguration*        collisionConfiguration;
    btCollisionDispatcher*                  dispatcher;
    btSequentialImpulseConstraintSolver*    solver;
    btDiscreteDynamicsWorld*                world;
    std::vector< std::shared_ptr<Body> >    bodies;
  public:
    PhysicsManager();
    void addBody( std::shared_ptr<Body> );
    void update();
};

#endif