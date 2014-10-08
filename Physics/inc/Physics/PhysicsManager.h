#ifndef __PHYSICS_PHYSICSMANAGER__
#define __PHYSICS_PHYSICSMANAGER__

#include <vector>
#include "btBulletDynamicsCommon.h"
#include "Physics/Body.h"
#include "Renderer/SGNode.h"
#include "Renderer/SceneGraph.h"

typedef enum _PhysicsState
{
  ON, OFF
} PhysicsState;

class PhysicsManager
{
  private:
    btBroadphaseInterface*                  broadphase;
    btDefaultCollisionConfiguration*        collisionConfiguration;
    btCollisionDispatcher*                  dispatcher;
    btSequentialImpulseConstraintSolver*    solver;
    btDiscreteDynamicsWorld*                world;
    std::vector< std::shared_ptr<Body> >    bodies;
    PhysicsState state;
  public:
    PhysicsManager();
    void addBody( std::shared_ptr<Body> );
    void update();
    void toggle();
    void turnOn() { this->state = ON; }
    void turnOff() { this->state = OFF; }
    PhysicsState getState() { return this->state; }
};

#endif