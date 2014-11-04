#include "Physics/PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
  this->state = OFF;

  broadphase = new btDbvtBroadphase();
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher( collisionConfiguration );
  solver = new btSequentialImpulseConstraintSolver();
  world = new btDiscreteDynamicsWorld( dispatcher, broadphase, solver, collisionConfiguration );
  world->setGravity( btVector3( 0, -9.8, 0 ) );

  btCollisionShape* groundShape = new btBoxShape( btVector3( 10, 0.1, 10 ) );

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

void PhysicsManager::toggle()
{
  if( state == ON ) state = OFF;
  else
  {
    state = ON;
    for( auto b : this->bodies ) b->update();
  }
}

void PhysicsManager::update()
{
  if( this->state == OFF ) return;

  this->world->stepSimulation( 1 / 60.f, 10 );
  for( std::shared_ptr<Body> body : this->bodies )
  {
    SGNodeWorldTransform w;
    WMath::vec3 t; WMath::quaternion q;

    t[0] = body->getBody()->getWorldTransform().getOrigin()[0];
    t[1] = body->getBody()->getWorldTransform().getOrigin()[1];
    t[2] = body->getBody()->getWorldTransform().getOrigin()[2];
    w.position = t;

    q[0] = body->getBody()->getWorldTransform().getRotation()[0];
    q[1] = body->getBody()->getWorldTransform().getRotation()[1];
    q[2] = body->getBody()->getWorldTransform().getRotation()[2];
    q[3] = body->getBody()->getWorldTransform().getRotation()[3];
    w.rotate = q;

    body->getSGNode()->setWorldTransform( w );
  }
}
