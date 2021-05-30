#include "../include/Scene.h"

Scene::Scene():
  models_(std::vector<Model>()),
  terrain_(Terrain())
{
  sm_ = ShaderManager(Assets::shaders);
}

Scene::~Scene(){}

void Scene::setupScene(){

  for(unsigned int i = 0; i < 10; i ++){
    models_.push_back(Model(&Assets::meshes.at("container"), "mainShader", sm_.program("mainShader"),
          glm::vec3(5 * cos(i), 2.0f, 5 * sin(i))));
    physicsEngine_.addObject(&models_.back(), COLLISION_SHAPES::CUBE);
  }
  
  //theire model 
  models_.push_back(Model(&Assets::meshes.at("theiere"), "mainShader", sm_.program("mainShader"),
        glm::vec3(4.0f, 10.0f, 0.0f)));
  physicsEngine_.addObject(&models_.back(), COLLISION_SHAPES::CONVEX_HULL);

  physicsEngine_.addTerrain(&terrain_);

  /* Initialization of lights */
  lights_ = {
    DirectionalLight(glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(-0.1f, -1.0f, 0.0f)),
    PointLight(glm::vec3(0.8f, 0.8f, 0.8f),
        glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(), &Assets::meshes.at("container"), sm_.program("lightingShader")),
    PointLight(glm::vec3(0.9f, 0.4f, 0.4f),
        glm::vec3(-1.0f, 3.0f, 0.0f), glm::vec3(), &Assets::meshes.at("container"), sm_.program("lightingShader")),
    PointLight(glm::vec3(0.4f, 0.9f, 0.0f),
        glm::vec3(0.0f, 6.0f, 0.0f), glm::vec3(), &Assets::meshes.at("container"), sm_.program("lightingShader")),
    PointLight(glm::vec3(0.1f, 0.1f, 0.8f),
        glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(), &Assets::meshes.at("container"), sm_.program("lightingShader"))
  }; 

  for(int i = 1; i < lights_.size(); i++){
    physicsEngine_.addObject(&lights_[i], COLLISION_SHAPES::CUBE, 0.05);
  }
  
  sm_.bindToModels(models_);
}


void Scene::drawScene(float deltaTime){

  deltaTime_ = deltaTime;
  frameCounter_++;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //stepSimulation();
  physicsEngine_.stepSimulation(deltaTime_);

  physics();   
  //physicsEngine_.updateWorldPhysics(deltaTime_);
  //std::cout << "drawing" << std::endl;

  // definition of matrices:
  if(State::perspective_){
    projectionMatrix_ = glm::perspective(glm::radians(45.0f),
          (float)1600 / (float)1200 , 0.1f, 1000.0f);
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

  // creates a new model (theier) to draw every 10000 frames.
  // and a new light
  if(frameCounter_ > 1000){
    models_.push_back(Model(&Assets::meshes.at("theiere"), "mainShader", sm_.program("mainShader"),
          glm::vec3(4.0f, 30.0f, 0.0f)));
    physicsEngine_.addObject(&models_.back(), COLLISION_SHAPES::CONVEX_HULL, 0.05);
    
    lights_.push_back(Light(LightType::POINT, glm::vec3(0.1f, 0.1f, 0.8f),
        glm::vec3(2.0f, 3.0f, 0.0f), glm::vec3(), &Assets::meshes.at("container"),
        sm_.program("lightingShader")));
    physicsEngine_.addObject(&lights_.back(), COLLISION_SHAPES::CUBE, 0.05);


    // need to rebind shader to models (extremelly inneficient)
    sm_.bindToModels(models_);

    frameCounter_ = 0;
  }
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

void Scene::physics(){
  //physicsEngine_.getDynamicsWorld()->stepSimulation(deltaTime_, 10);

  //print position of objects
  for (int j = physicsEngine_.getDynamicsWorld()->getNumCollisionObjects() - 1; j >= 0; j--)
  {
    btCollisionObject* obj = physicsEngine_.getDynamicsWorld()->getCollisionObjectArray()[j];
    btRigidBody* body = btRigidBody::upcast(obj);
    btTransform trans;
    if (body && body->getMotionState()) {
        body->getMotionState()->getWorldTransform(trans);
    }
    else {
        trans = obj->getWorldTransform();
    }
    // update model position and orientation
    if(findModel(body) != nullptr){
      findModel(body)->updatePosition(trans);
    }
  }
}

void Scene::stepSimulation(){
  physicsEngine_.getDynamicsWorld()->stepSimulation(deltaTime_, 10);
}

Model* Scene::findModel(btRigidBody* body){
  for (size_t i = 0; i < models_.size(); i++){
    if(body != nullptr && models_[i].getRigidBody() != nullptr ){
      if(body == models_[i].getRigidBody()){
        return &models_[i];
      }
    }
  }
  for (size_t i = 0; i < lights_.size(); i++){
    if(body != nullptr && lights_[i].getRigidBody() != nullptr ){
      if(body == lights_[i].getRigidBody()){
        return &lights_[i];
      }
    }
  }
  return nullptr;
}

// TODO have lights move with deltaTime
// TODO better lighting system, (maybe Entity class?)
// TODO include spot light handling in shaders...
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

// TODO Mouse picking (with bullet physics?)
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
