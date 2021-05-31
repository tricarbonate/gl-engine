#include "../include/PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() :
    worldGravity_(-3)
{
  collisionConfiguration_ = new btDefaultCollisionConfiguration();
  dispatcher_ = new btCollisionDispatcher(collisionConfiguration_);
  overlappingPairCache_ = new btDbvtBroadphase();
  solver_ = new btSequentialImpulseConstraintSolver;

  dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher_,
    overlappingPairCache_, solver_, collisionConfiguration_);

  dynamicsWorld_->setGravity(btVector3(0, worldGravity_, 0));
}

PhysicsEngine::~PhysicsEngine()
{}

void PhysicsEngine::addObject(Model* model, COLLISION_SHAPES shape, double data){
    model->initPhysics(dynamicsWorld_, shape, data);

    dynamicsWorld_->addRigidBody(model->getRigidBody());
    corels_[model->getRigidBody()] = model;
    objects_.push_back(model);
}

void PhysicsEngine::addTerrain(Terrain* terrain){
    terrain_ = terrain;
    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.0f), btScalar(1.0f), btScalar(50.0f)));

    collisionShapes_.push_back(groundShape);

    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, terrain_->getBaseHeight() - 1.0f, 0));

    btScalar mass(0);
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        groundShape->calculateLocalInertia(mass, localInertia);

    btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
    btRigidBody* body = new btRigidBody(rbInfo);

    //add the body to the dynamics world
    dynamicsWorld_->addRigidBody(body);
}

void PhysicsEngine::addHeightField(Terrain* terrain){
  heightfieldShape_ = new btHeightfieldTerrainShape(terrain->getWidth(), terrain->getLength(),
      terrain->getRawData(), terrain->getHeightScale(),
      terrain->getMinHeight(), terrain->getMaxHeight(),
      1, PHY_FLOAT, false); 
}


void PhysicsEngine::updateWorldPhysics(double deltaTime)
{
    
    dynamicsWorld_->stepSimulation(deltaTime, 10);
    
    //print position of objects
    for (int j = dynamicsWorld_->getNumCollisionObjects() - 1; j >= 0; j--)
    {
        btCollisionObject* obj = dynamicsWorld_->getCollisionObjectArray()[j];
        btRigidBody* body = btRigidBody::upcast(obj);
        btTransform trans;
        if (body && body->getMotionState()) {
            body->getMotionState()->getWorldTransform(trans);
        }
        else {
            trans = obj->getWorldTransform();
        }

        if(corels_.count(body) > 0){
          corels_.at(body)->updatePosition(trans);
        }
        
    }
}

Model* PhysicsEngine::getPickedModel(){
  return corels_[pickedBody_];
}

bool PhysicsEngine::pickBody(const btVector3& rayFromWorld, const btVector3& rayToWorld){
  if(dynamicsWorld_ == 0)
    return false;

  btCollisionWorld::ClosestRayResultCallback rayCallback(rayFromWorld, rayToWorld);

  rayCallback.m_flags |= btTriangleRaycastCallback::kF_UseGjkConvexCastRaytest;
  dynamicsWorld_->rayTest(rayFromWorld, rayToWorld, rayCallback);
  if(rayCallback.hasHit())
  {
    btVector3 pickPos = rayCallback.m_hitPointWorld;
    btRigidBody* body = (btRigidBody*)btRigidBody::upcast(rayCallback.m_collisionObject);
    if (body)
    {
      //other exclusions?
      if (!(body->isStaticObject() || body->isKinematicObject()))
      {
      pickedBody_ = body;
      savedState_ = pickedBody_->getActivationState();
      pickedBody_->setActivationState(DISABLE_DEACTIVATION);
      std::cout << pickPos.getX() << pickPos.getY() << pickPos.getZ() << std::endl;
      btVector3 localPivot = body->getCenterOfMassTransform().inverse() * pickPos;
      btPoint2PointConstraint* p2p = new btPoint2PointConstraint(*body, localPivot);
      dynamicsWorld_->addConstraint(p2p, true);
      pickedConstraint_ = p2p;
      btScalar mousePickClamping = 100.f;
      p2p->m_setting.m_impulseClamp = mousePickClamping;
      //very weak constraint for picking
      p2p->m_setting.m_tau = 0.001f;
      }
    }

    //pickObject(pickPos, rayCallback.m_collisionObject);
    oldPickingPos_ = rayToWorld;
    hitPos_ = pickPos;
    oldPickingDist_ = (pickPos - rayFromWorld).length();
    std::cout << "HIT" << std::endl;
    return true;
    //add p2p
  }
  return false;
}


bool PhysicsEngine::movePickedBody(const btVector3& rayFromWorld, const btVector3& rayToWorld){
  if (pickedBody_ && pickedConstraint_)
  {
    btPoint2PointConstraint* pickCon = static_cast<btPoint2PointConstraint*>(pickedConstraint_);
    if (pickCon)
    {
      //keep it at the same picking distance
      btVector3 newPivotB;

      btVector3 dir = rayToWorld - rayFromWorld;
      dir.normalize();
      dir *= oldPickingDist_;

      newPivotB = rayFromWorld + dir;
      pickCon->setPivotB(newPivotB);
      return true;
    }
  }
  return false;
}

void PhysicsEngine::removePickingConstraint(){
  if(pickedConstraint_){
    pickedBody_->forceActivationState(savedState_);
    pickedBody_->activate();
    dynamicsWorld_->removeConstraint(pickedConstraint_);
    delete pickedConstraint_;
    pickedConstraint_ = 0;
    pickedBody_ = 0;
  }
}


