#include "../include/PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() :
    worldGravity_(-3)
{
  dynamicsWorld_->setGravity(btVector3(0, worldGravity_, 0));
}

PhysicsEngine::~PhysicsEngine()
{}

void PhysicsEngine::addObject(Model* model, COLLISION_SHAPES shape, double data){
    model->initPhysics(dynamicsWorld_, shape, data);
    //model->getRigidBody()->setGravity(btVector3(0, worldGravity_, 0));

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

void PhysicsEngine::stepSimulation(double deltaTime){
  dynamicsWorld_->stepSimulation(deltaTime, 10);
}

void PhysicsEngine::updateWorldPhysics(double deltaTime){
    

    //dynamicsWorld_->stepSimulation(deltaTime, 10);
    
    std::cout << dynamicsWorld_ << std::endl;

    //print position of objects
    for (int j = dynamicsWorld_->getNumCollisionObjects() - 1; j >= 0; j--)
    {
        std::cout << j << std::endl;
        btCollisionObject* obj = dynamicsWorld_->getCollisionObjectArray()[j];
        btRigidBody* body = btRigidBody::upcast(obj);
        btTransform trans;
        if (body && body->getMotionState()) {
            body->getMotionState()->getWorldTransform(trans);
        }
        else {
            trans = obj->getWorldTransform();
        }


        /*
        // update model position and orientation
        if(corels_.count(body) > 0){
          if(corels_.at(body) != nullptr){
            //std::cout << "nullptr" << std::endl;
            corels_.at(body)->updatePosition(trans);
          }
          else{
            //std::cout << "nullptr" << std::endl;
          }
        }
        else{
          
        }
        */
        if(findModel(body) != nullptr){
          findModel(body)->updatePosition(trans);
        }
        
    }
    std::cout << deltaTime << std::endl;
}


Model* PhysicsEngine::findModel(btRigidBody* body){
  for (size_t i = 0; i < objects_.size(); i++){
    if(body != nullptr && objects_[i]->getRigidBody() != nullptr ){
      if(body == objects_[i]->getRigidBody()){
        std::cout << objects_[i]->getPosition().r << std::endl;
        return objects_[i];
      }
    }
  }
  return nullptr;
}
