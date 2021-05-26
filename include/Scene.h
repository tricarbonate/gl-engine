#ifndef SCENE_H
#define SCENE_H

#include "includes.h"

#include <bullet/btBulletDynamicsCommon.h>

#include <vector>
#include <map>
#include <unordered_map>

static const double GRAVITY_ACCELERATION = -0.0;

/*
 * The scene contains all the elements
 * to render */
class Scene{

  public:

    Scene();
    ~Scene();

    void setupScene();

    // setup matrices values
    // and call drawLights(), drawEntities() and drawTerrain()
    void drawScene(float deltaTime);

    // draw the mirrors
    void drawMirrors();

    Camera* getCamera() { return &camera_; }

    void physics();

  private:

    Terrain terrain_;
    std::unordered_map<std::string, Texture> textures_;
    std::unordered_map<std::string, Material> materials_;
    std::unordered_map<std::string, Mesh> meshes_;
    std::vector<Model> models_;
    std::vector<Mirror> mirrors_;
    std::vector<Light> lights_;

    ShaderManager sm_; 

    float deltaTime_;

    double test_ = 0.0f;

    Camera camera_;
    glm::mat4 modelMatrix_, viewMatrix_, projectionMatrix_, mvp_;

    void defineTextures();
    void defineMaterials();
    void defineMeshes();

    /* private methods for setup and drawing: */

    // draw all the lights in 'lights_'
    void drawLights();

    // draw all models, meshes, entities
    void drawEntities();

    // draw the terrain
    void drawTerrain();


    /* Bullet Physics */

    //setup default configuration for collision detection
    btDefaultCollisionConfiguration* collisionConfiguration_ = new btDefaultCollisionConfiguration();
     
    btCollisionDispatcher* dispatcher_ = new btCollisionDispatcher(collisionConfiguration_);

	btBroadphaseInterface* overlappingPairCache_ = new btDbvtBroadphase();

    btSequentialImpulseConstraintSolver* solver_ = new btSequentialImpulseConstraintSolver;

	btDiscreteDynamicsWorld* dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher_,
        overlappingPairCache_, solver_, collisionConfiguration_);


    btAlignedObjectArray<btCollisionShape*> collisionShapes_;

    /* */ 

    int frameCounter_ = 0;
};


#endif //SCENE_H
