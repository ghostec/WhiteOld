#ifndef __PHYSICS_BODY__
#define __PHYSICS_BODY__

#include <iostream>
#include <memory>
#include "btBulletDynamicsCommon.h"
#include "Renderer/Model.h"

class Body
{
  private:
    btCollisionShape* shape;
    btRigidBody* body;
    std::shared_ptr<Model> model;
  public:
    Body( std::shared_ptr<Model> model, bool is_static = false );
    btRigidBody* getBody() { return this->body; }
    std::shared_ptr<Model> getModel() { return this->model; }
};

#endif