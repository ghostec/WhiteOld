#include "Physics/PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
  broadphase = new btDbvtBroadphase();
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher( collisionConfiguration );
  solver = new btSequentialImpulseConstraintSolver();
  world = new btDiscreteDynamicsWorld( dispatcher, broadphase, solver, collisionConfiguration );
  world->setGravity( btVector3( 0, -2, 0 ) );

  btCollisionShape* groundShape = new btBoxShape( btVector3( 10, 1, 10 ) );

  btDefaultMotionState* groundMotionState = new btDefaultMotionState( btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, -1, 0 ) ) );
  btRigidBody::btRigidBodyConstructionInfo
    groundRigidBodyCI( 0, groundMotionState, groundShape, btVector3( 0, 0, 0 ) );
  btRigidBody* groundRigidBody = new btRigidBody( groundRigidBodyCI );
  this->world->addRigidBody( groundRigidBody );
}

void PhysicsManager::addBody( std::shared_ptr<Body> body )
{
  this->bodies.push_back( body );
  this->world->addRigidBody( body->getBody() );
}

void PhysicsManager::update()
{
  this->world->stepSimulation( 1 / 60.f, 10 );
  for( std::shared_ptr<Body> body : this->bodies )
  {
    WMath::vec3 v;
    v[0] = body->getBody()->getWorldTransform().getOrigin()[0];
    v[1] = body->getBody()->getWorldTransform().getOrigin()[1];
    v[2] = body->getBody()->getWorldTransform().getOrigin()[2];
    std::cout << v[0] << " " << v[1] << " " << v[2] << std::endl;
    WMath::setOrigin( body->getModel()->getTranslateM(), v );
  }
}