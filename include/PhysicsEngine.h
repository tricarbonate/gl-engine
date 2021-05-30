#ifndef __PHYSICS_ENGINE_H__
#define __PHYSICS_ENGINE_H__

#include <bullet/btBulletDynamicsCommon.h>

#include <vector>
#include <memory>

#include "Model.h"
#include "Terrain.h"

/* 
 * This class knows about all world Objects, define and updates physical properties
 * of these objects, and connect these information with Bullet Physics Engine.
 */
class PhysicsEngine{
  public:
    PhysicsEngine();
    ~PhysicsEngine();

    void addObject(Model* model, COLLISION_SHAPES shape = CUBE, double data = 0.5);
    void addTerrain(Terrain* terrain);

    void updateWorldPhysics(double deltaTime);

    btDiscreteDynamicsWorld* getDynamicsWorld() { return dynamicsWorld_; }


  private:
    std::vector<Model*> objects_; // objects_ contains pointers to all models (including lights)
    Terrain* terrain_; //for now a pointer to the terrain

    const double worldGravity_;



    btDefaultCollisionConfiguration* collisionConfiguration_ = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher_ = new btCollisionDispatcher(collisionConfiguration_);
    btBroadphaseInterface* overlappingPairCache_ = new btDbvtBroadphase();
    btSequentialImpulseConstraintSolver* solver_ = new btSequentialImpulseConstraintSolver;

    btDiscreteDynamicsWorld* dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher_,
	overlappingPairCache_, solver_, collisionConfiguration_);

    btAlignedObjectArray<btCollisionShape*> collisionShapes_;

    // Helps to find the correspond world model of a btRigidBody quicklier
    std::unordered_map<btRigidBody*, Model*> corels_;
};

#endif // __PHYSICS_ENGINE_H__
