#ifndef __PHYSICS_BODY__
#define __PHYSICS_BODY__

#include <iostream>
#include <memory>
#include "btBulletDynamicsCommon.h"
#include "Renderer/Model.h"
#include "Renderer/SGNode.h"

class Body
{
  private:
    btCollisionShape* shape;
    btRigidBody* body;
    std::shared_ptr<SGNode> sg_node;
  public:
    Body( std::shared_ptr<SGNode> sg_node, bool is_static = false );
    void update();
    btRigidBody* getBody() { return this->body; }
    std::shared_ptr<SGNode> getSGNode() { return this->sg_node; }
};

#endif