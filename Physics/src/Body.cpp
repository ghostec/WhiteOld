#include "Physics/Body.h"

Body::Body( std::shared_ptr<SGNode> sg_node, bool is_static )
{
  static float test = 0;
  this->sg_node = sg_node;

  btTriangleMesh* mesh = new btTriangleMesh();

  std::shared_ptr<Model> model = sg_node->getModel();

  const std::vector< std::array< GLushort, 3 > > elements =
    model->getMesh()->getElements();

  const std::vector< WMath::vec3 > vertices = model->getMesh()->getVertices();

  for( int i = 0; i < model->getMesh()->getVerticesCount(); i += 3 )
  {
    WMath::vec3 v1 = vertices[ elements[ i ][0] ];
    WMath::vec3 v2 = vertices[ elements[ i + 1 ][0] ];
    WMath::vec3 v3 = vertices[ elements[ i + 2 ][0] ];

    btVector3 bv1 = btVector3( v1[0], v1[1], v1[2] );
    btVector3 bv2 = btVector3( v2[0], v2[1], v2[2] );
    btVector3 bv3 = btVector3( v3[0], v3[1], v3[2] );

    mesh->addTriangle( bv1, bv2, bv3 );
  }

  if( !is_static )
  {
    SGNodeWorldTransform w = sg_node->getWorldTransform();
    this->shape = new btBoxShape( btVector3( 1, 1, 1 ) );
    WMath::vec3 p = w.position;
    btVector3 position = btVector3( p[0], p[1], p[2] );

    btDefaultMotionState* motionState = new btDefaultMotionState( btTransform( btQuaternion( 0, 0, 0, 1 ), position ) );

    btScalar bodyMass = 1;
    btVector3 bodyInertia;
    this->shape->calculateLocalInertia( bodyMass, bodyInertia );

    btRigidBody::btRigidBodyConstructionInfo bodyCI = btRigidBody::btRigidBodyConstructionInfo( bodyMass, motionState, shape, bodyInertia );

    bodyCI.m_restitution = 0.4f;
    bodyCI.m_friction = 0.6f;

    this->body = new btRigidBody( bodyCI );

    //this->body->setLinearFactor( btVector3( 1, 1, 1 ) );
  }
  else
  {
    this->shape = new btBoxShape( btVector3( 20, 0, 20 ) );
    btDefaultMotionState* groundMotionState =
      new btDefaultMotionState( btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, 0, 0 ) ) );
    btRigidBody::btRigidBodyConstructionInfo
      groundRigidBodyCI( 0, groundMotionState, this->shape, btVector3( 0, 0, 0 ) );
    this->body = new btRigidBody( groundRigidBodyCI );
  }
}

void Body::update()
{
  // TODO: propagate parent->child transforms
  btTransform tr; this->body->getMotionState()->getWorldTransform( tr );
  SGNodeWorldTransform w = sg_node->getWorldTransform();
  WMath::vec3 p = w.position;
  WMath::quaternion q = w.rotate;
  btVector3 position = btVector3( p[0], p[1], p[2] );
  tr.setOrigin( position );
  tr.setRotation( btQuaternion( q[0], q[1], q[2], q[3] ) );
  this->body->setWorldTransform( tr );
}
