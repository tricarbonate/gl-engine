#ifndef __PHYSICS_ENGINE_H__
#define __PHYSICS_ENGINE_H__

#include <bullet/btBulletDynamicsCommon.h>
#include <BulletCollision/NarrowPhaseCollision/btRaycastCallback.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>

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
    void addHeightField(Terrain* terrain);

    void updateWorldPhysics(double deltaTime);

    btDiscreteDynamicsWorld* getDynamicsWorld() { return dynamicsWorld_; }

    bool pickBody(const btVector3& rayFromWorld, const btVector3& rayToWorld);
    bool movePickedBody(const btVector3& rayFromWorld, const btVector3& rayToWorld);
    void removePickingConstraint();

    Model* getPickedModel();

  private:
    std::vector<Model*> objects_; // objects_ contains pointers to all models (including lights)
    Terrain* terrain_; //for now a pointer to the terrain

    const double worldGravity_;

    /* BULLET PHYSICS */
    btDefaultCollisionConfiguration* collisionConfiguration_;
    btCollisionDispatcher* dispatcher_;
    btBroadphaseInterface* overlappingPairCache_;
    btSequentialImpulseConstraintSolver* solver_;
    btDiscreteDynamicsWorld* dynamicsWorld_;
    btAlignedObjectArray<btCollisionShape*> collisionShapes_;

    /* data for picking object */
    class btRigidBody* pickedBody_;
    class btTypedConstraint* pickedConstraint_;
    int savedState_;
    btVector3 oldPickingPos_;
    btVector3 hitPos_;
    btScalar oldPickingDist_;


    /* Terrain heightfield */
    btHeightfieldTerrainShape* heightfieldShape_;

    // Helps to find the correspond world model of a btRigidBody quicklier
    std::unordered_map<btRigidBody*, Model*> corels_;
};

#endif // __PHYSICS_ENGINE_H__
