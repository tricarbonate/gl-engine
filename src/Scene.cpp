#include "../include/Scene.h"

Scene::Scene(GLFWwindow* window, PhysicsEngine* engine):
  models_(std::vector<Model>()),
  terrain_(Terrain()),
  physicsEngine_(engine),
  window_(window)
{
  models_.reserve(State::nMaxModels);
  lights_.reserve(State::nMaxLights);
  sm_ = ShaderManager(Assets::shaders);
}

Scene::~Scene(){}

void Scene::setupScene(){

  //containers
  for(unsigned int i = 0; i < 1; i ++){
    models_.push_back(Model("container", "mainShader", sm_.program("mainShader"),
          glm::vec3(5 * cos(i), 20 * tan(i), 5 * sin(i))));
    physicsEngine_->addObject(&models_.back(), COLLISION_SHAPES::CUBE);
  }
  
  
  /*theire model 
  models_.push_back(Model("theiere", "mainShader", sm_.program("mainShader"),
        glm::vec3(4.0f, 10.0f, 0.0f)));
  physicsEngine_.addObject(&models_.back(), COLLISION_SHAPES::CONVEX_HULL); 
  */

  physicsEngine_->addTerrain(&terrain_);

  /* Initialization of lights */
  lights_ = {
    DirectionalLight(glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(0.0f, -1.0f, 0.0f)),
    PointLight(glm::vec3(0.8f, 0.8f, 0.8f),
        glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(), "container", sm_.program("lightingShader")),
    PointLight(glm::vec3(0.9f, 0.4f, 0.4f),
        glm::vec3(-1.0f, 3.0f, 0.0f), glm::vec3(), "container", sm_.program("lightingShader")),
    PointLight(glm::vec3(0.4f, 0.9f, 0.0f),
        glm::vec3(0.0f, 6.0f, 0.0f), glm::vec3(), "container", sm_.program("lightingShader")),
    PointLight(glm::vec3(0.1f, 0.1f, 0.8f),
        glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(), "container", sm_.program("lightingShader"))
  }; 

  
  sm_.bindToModels(models_);
  for(size_t i = 1; i < lights_.size(); i++){
    //Oversized collision shape to facilitate light picking
    physicsEngine_->addObject(&lights_[i], COLLISION_SHAPES::CUBE, 0.5);
  }
  std::cout << models_.size() << std::endl;
}


void Scene::drawScene(float deltaTime){

  deltaTime_ = deltaTime;
  frameCounter_++;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  physicsEngine_->updateWorldPhysics(deltaTime_);

  // definition of matrices:
  if(State::perspective_){
    projectionMatrix_ = glm::perspective(glm::radians(State::fov_),
          State::screenWidth_ / State::screenHeight_, State::nearPlane_, State::farPlane_);
  }
  else{
    projectionMatrix_ = glm::ortho(-3.0, 3.0, -3.0, 3.0, 1.0, 100.0);
  }


  viewMatrix_ = camera_.lookAt();
  modelMatrix_ = glm::mat4(1.0f);
  mvp_ = projectionMatrix_ * viewMatrix_ * modelMatrix_;

  drawEntities();
  drawLights();
  drawTerrain();

  
  if(State::picking_){
    GLdouble xpos, ypos;
    glfwGetCursorPos(window_, &xpos, &ypos);
    btVector3 rayTo = getRayTo(int(xpos), int(ypos));
    glm::vec3 vec = camera_.getPos();
    btVector3 rayFrom = btVector3(vec.r, vec.g, vec.b);
    Model* pickedModel = nullptr;
    if(!hasPicked_){
      hasPicked_ = physicsEngine_->pickBody(rayFrom, rayTo);
    }
    else{
      //physicsEngine_.movePickedBody(rayFrom, rayTo);
    }
  }
  else{
    physicsEngine_->removePickingConstraint();
    hasPicked_ = false;
  }

  // creates a new model (theier) to draw every 10000 frames.
  // and a new light
  if(frameCounter_ > 200){
    models_.push_back(Model("container", "mainShader", sm_.program("mainShader"),
          randomVec3(1, 10)));
    physicsEngine_->addObject(&models_.back(), COLLISION_SHAPES::CUBE, 0.5);
    
    /*
    lights_.push_back(Light(LightType::POINT, glm::vec3(0.1f, 0.1f, 0.8f),
        randomVec3(-10, 10), glm::vec3(), "container",
        sm_.program("lightingShader")));
    physicsEngine_.addObject(&lights_.back(), COLLISION_SHAPES::CUBE, 0.05);
    */


    // need to rebind shader to models (extremelly inneficient)
    sm_.bindToModels(models_);

    frameCounter_ = 0;
  }

  /*
  if(frameCounter_ > 100){

    for (size_t i = 0; i < models_.size(); i++){
      btTransform trans;
      glm::vec3 vec = models_[i].getPosition() + randomVec3(0.001, 0.01);
      trans.setOrigin(btVector3(vec.r, vec.g, vec.b));
      models_[i].updatePosition(trans);
    }
  }
  */
}


void Scene::drawLights(){
  //glUseProgram(0);
  sm_.program("lightingShader")->useProgram();
  for(unsigned int i = 0; i < lights_.size(); i++){
    if(lights_[i].getType() == LightType::POINT){
      modelMatrix_ = glm::mat4(1.0f);
      modelMatrix_ = glm::translate(modelMatrix_, lights_[i].getPosition());
      modelMatrix_ = glm::scale(modelMatrix_ , glm::vec3(0.2f));
      mvp_ = projectionMatrix_ * viewMatrix_ * modelMatrix_;
      sm_.program("lightingShader")->setUniform("lightColor", lights_[i].getDiffuseColor());
      sm_.program("lightingShader")->setUniform("mvp", mvp_);
      lights_[i].getMesh()->renderMesh();
    }
  }
}

void Scene::drawEntities(){

  // draw all models:
  // for all shader programs that exists, draw their corresponding models
  for(auto it = sm_.getShaders().begin(); it != sm_.getShaders().end(); it++){
    it->second.first.useProgram();
    it->second.first.setUniform("viewPos", camera_.getPos());
    it->second.first.setUniformLights(lights_);
    
    for(unsigned int i = 0; i < it->second.second.size(); i++){
      
      // translate and rotate each model to its correct position and orientation
      // and send model and mvp to shader
      modelMatrix_ = glm::mat4(1.0f); 
      modelMatrix_ = glm::translate(modelMatrix_, it->second.second[i]->getPosition());

      modelMatrix_ = glm::rotate(modelMatrix_, it->second.second[i]->getOrientation().r, glm::vec3(1, 0, 0));
      modelMatrix_ = glm::rotate(modelMatrix_, it->second.second[i]->getOrientation().g, glm::vec3(0, 1, 0));
      modelMatrix_ = glm::rotate(modelMatrix_, it->second.second[i]->getOrientation().b, glm::vec3(0, 0, 1));

      mvp_ = projectionMatrix_ * viewMatrix_ * modelMatrix_;
      it->second.first.setUniform("mvp", mvp_);
      it->second.first.setUniform("model", modelMatrix_);
      it->second.second[i]->draw();
    }
  }
}

void Scene::drawTerrain(){
  sm_.program("terrain_flatshader")->useProgram();  
  sm_.program("terrain_flatshader")->setUniform("viewPos", camera_.getPos());
  sm_.program("terrain_flatshader")->setUniformLights(lights_);

  terrain_.draw(modelMatrix_, viewMatrix_, projectionMatrix_, *sm_.program("terrain_flatshader"));
}


void Scene::addModel(Model model){
  models_.push_back(model);
  physicsEngine_->addObject(&models_.back());
  sm_.bindToModels(models_);  
}

btVector3 Scene::getRayTo(int x, int y){
  btVector3 rayFrom, rayDir;

  rayFrom = btVector3(camera_.getPos().r, camera_.getPos().g, camera_.getPos().b);
  rayDir = btVector3(camera_.getFront().r, camera_.getFront().g, camera_.getFront().b);

  rayDir.normalize();
  rayDir *= State::farPlane_;
  //btVector3 rightOffset;
  btVector3 vertical(0, 1, 0);
  btVector3 horizontal = rayDir.cross(vertical);
  horizontal.safeNormalize();
  vertical = horizontal.cross(rayDir);
  vertical.safeNormalize();

  float tanfov = tanf(0.5f * glm::radians(State::fov_));
  horizontal *= 2.0f * State::farPlane_ * tanfov;
  vertical *= 2.0f * State::farPlane_ * tanfov;

  btScalar aspect = State::screenWidth_ / State::screenHeight_;
  horizontal *= aspect;

  btVector3 rayToCenter = rayFrom + rayDir;
  btVector3 dHor = horizontal * 1.0f / State::screenWidth_;
  btVector3 dVert = vertical * 1.0f / State::screenHeight_;
  btVector3 rayTo = rayToCenter - 0.5f * horizontal + 0.5f * vertical;
  rayTo += btScalar(x) * dHor;
  rayTo -= btScalar(y) * dVert;
  return rayTo;
}

// TODO have lights move with deltaTime
// TODO better lighting system, (maybe Entity class?)
// TODO include spot light handling in shaders...
// TODO DirectionalLight is a special case... delete the class and find another solution
//
// TODO class that handles movement,
// TODO syncing with bullet physics and entities positions
// physics variables, communication with bullet physics in relation with deltaTime
//
// TODO Find a real idea
//
// TODO More State Handling to use imgui
// TODO More imgui functionalities

// TODO Scene class should only contain entities initialization and drawing.
//
// TODO Find a serialization library
//
// TODO change sm_.bindToModels to accept only one new model

// TODO Mouse picking (with bullet physics?)
// TODO Should not pick the terrain
// TODO Add a shader for picked object
// TODO Move rayTo() function (where?)
// TODO Controller inputs?

// TODO More usable Terrain class
// TODO Create a mesh from Chunk?
// TODO Learn about Chunk creation...
// TODO btHeightfield
//
// TODO Change makefile to compile .h .cpp recursively (folders)
//
//
// TODO GLSL Cleaner uniform data structures (in struct... out struct)
// TODO Uniform Buffer Objects
// TODO Andvanced GLSL (learnopengl.com)
// TODO Geometry and tesselation shaders
// TODO Antialiasing (learnopengl.com)
// TODO Normal Mapping
// TODO Bloom effect for lights
//
// TODO Faire une map sur papier des classes Models, Mesh etc...
//
// TODO boost::flyweight (juste savoir ce que c'est...)
//
// TODO !!!! Search for and learn to use good debugging tools
// TODO search for boost::ptr_vector
//
//
// TODO Cleanup functions for pointers :
// - Custurm pointers...
// - bullet physics cleanup...
// - gl and window cleanup...
//
// TODO Add debug functions
//
// TODO Change aspect ratio (perspective) for window resizes
