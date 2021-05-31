#ifndef SCENE_H
#define SCENE_H

//#include "includes.h"
#include "Model.h"
#include "Light.h"
#include "ShaderManager.h"
#include "Mirror.h"
#include "Camera.h"
#include "Terrain.h"
#include "Assets.h"
#include "PhysicsEngine.h"
#include "DirectionalLight.h"
#include "utils.hpp"
#include "PointLight.h"

#include <bullet/btBulletDynamicsCommon.h>

#include <vector>
#include <map>
#include <unordered_map>


/*
 * The scene contains all the elements
 * to render */
class Scene{

  public:

    Scene(GLFWwindow* window);
    ~Scene();

    void setupScene();
    void drawScene(float deltaTime);

    Camera* getCamera() { return &camera_; }

    void addModel(Model model);

  private:

    std::vector<Model> models_;
    std::vector<Mirror> mirrors_;
    std::vector<Light> lights_;

    GLFWwindow* window_;

    Terrain terrain_;

    ShaderManager sm_; 
    PhysicsEngine physicsEngine_;

    double deltaTime_;

    double test_ = 0.0f;
    double hasPicked_ = false;

    Camera camera_;
    glm::mat4 modelMatrix_, viewMatrix_, projectionMatrix_, mvp_;

    btVector3 getRayTo(int x, int y);

    void drawLights();
    void drawEntities();
    void drawTerrain();

    /* */ 
    int frameCounter_ = 0;
};


#endif //SCENE_H
