#include "../include/Scene.h"

Scene::Scene(GLFWwindow* window, PhysicsEngine* engine):
  models_(std::vector<Model>()),
  window_(window),
  terrain_(Terrain()),
  physicsEngine_(engine)
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
  
  
  //theire model 
  models_.push_back(Model("theiere", "mainShader", sm_.program("mainShader"),
        glm::vec3(4.0f, 10.0f, 0.0f)));
  physicsEngine_->addObject(&models_.back(), COLLISION_SHAPES::CONVEX_HULL); 
  

  physicsEngine_->addTerrain(&terrain_);

  /* Initialization of lights */
  lights_ = {
    DirectionalLight(glm::vec3(0.4f, 0.2f, 0.2f),
        glm::vec3(0.0f, -1.0f, 0.0f))
/*    PointLight(glm::vec3(0.8f, 0.8f, 0.8f),
        glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(), "container", sm_.program("lightingShader")),
    PointLight(glm::vec3(0.9f, 0.4f, 0.4f),
        glm::vec3(-1.0f, 3.0f, 0.0f), glm::vec3(), "container", sm_.program("lightingShader")),
    PointLight(glm::vec3(0.4f, 0.9f, 0.0f),
        glm::vec3(0.0f, 6.0f, 0.0f), glm::vec3(), "container", sm_.program("lightingShader")),
    PointLight(glm::vec3(0.1f, 0.1f, 0.8f),
        glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(), "container", sm_.program("lightingShader"))*/
  }; 

  
  sm_.bindToModels(models_);
  for(size_t i = 1; i < lights_.size(); i++){
    //Oversized collision shape to facilitate light picking
    physicsEngine_->addObject(&lights_[i], COLLISION_SHAPES::CUBE, 1);
  }



  /* FRAME BUFFER VAO */
  glGenVertexArrays(1, &quadVAO);
  glGenBuffers(1, &quadVBO);
  glBindVertexArray(quadVAO);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

  /* FRAME BUFFER CREATION */
  glGenFramebuffers(1, &fbo); 
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, State::screenWidth_, State::screenHeight_,
      0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // attach the texture to the framebuffer.
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

  unsigned int rbo;
  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, State::screenWidth_, State::screenHeight_);  
  //glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);  

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
  glBindFramebuffer(GL_FRAMEBUFFER, 0);


  /* MIRROR FRAME BUFFER VAO */
  glGenVertexArrays(1, &mirrorVAO);
  glGenBuffers(1, &mirrorVBO);
  glBindVertexArray(mirrorVAO);
  glBindBuffer(GL_ARRAY_BUFFER, mirrorVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

  /* MIRROR FRAME BUFFER CREATION */
  glGenFramebuffers(1, &mirrorFbo); 
  glBindFramebuffer(GL_FRAMEBUFFER, mirrorFbo);

  glGenTextures(1, &mirroredTex);
  glBindTexture(GL_TEXTURE_2D, mirroredTex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, State::screenWidth_, State::screenHeight_,
      0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // attach the texture to the framebuffer.
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mirroredTex, 0);

  unsigned int mirrorRbo;
  glGenRenderbuffers(1, &mirrorRbo);
  glBindRenderbuffer(GL_RENDERBUFFER, mirrorRbo); 
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, State::screenWidth_, State::screenHeight_);  
  //glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mirrorRbo);  

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Scene::drawScene(float deltaTime){

  deltaTime_ = deltaTime;
  frameCounter_++;

  physicsEngine_->updateWorldPhysics(deltaTime_);
  if(State::picking_){
    GLdouble xpos, ypos;
    glfwGetCursorPos(window_, &xpos, &ypos);
    if(State::cursorDisabled_){
      xpos = State::screenWidth_ / 2;
      ypos = State::screenHeight_ / 2;
    }
    btVector3 rayTo = getRayTo(int(xpos), int(ypos));
    glm::vec3 vec = camera_.getPos();
    btVector3 rayFrom = btVector3(vec.r, vec.g, vec.b);
    if(!hasPicked_){
      hasPicked_ = physicsEngine_->pickBody(rayFrom, rayTo);
    }
    else{
      physicsEngine_->movePickedBody(rayFrom, rayTo);
    }
  }
  else{
    physicsEngine_->removePickingConstraint();
    hasPicked_ = false;
  }


  //viewMatrix_ = camera_.lookAt();
  modelMatrix_ = glm::mat4(1.0f);
  mvp_ = projectionMatrix_ * viewMatrix_ * modelMatrix_;


  /* Draw normal scene */
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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

  // creates a new model (theier) to draw every 10000 frames.
  // and a new light
  if(frameCounter_ > 200){
    models_.push_back(Model("theiere", "mainShader", sm_.program("mainShader"),
          randomVec3(-20, 20, glm::vec3(1, 0, 1))));
    physicsEngine_->addObject(&models_.back(), COLLISION_SHAPES::CONVEX_HULL, 0.5);
     
   
    lights_.push_back(Light(LightType::POINT, randomVec3(0, 0.8),
        randomVec3(-20, 20, glm::vec3(1, 0, 1)), glm::vec3(), "container",
        sm_.program("lightingShader")));
    physicsEngine_->addObject(&lights_.back(), COLLISION_SHAPES::CUBE, 1);
    
    
    sm_.bindToModel(models_.back());

    frameCounter_ = 0;
  }

  if(State::useGammaCorrection_)
    glEnable(GL_FRAMEBUFFER_SRGB);
  else
    glDisable(GL_FRAMEBUFFER_SRGB);


  //after everything is drawn, draw a quad in the default framebuffer, with a texture being the content
  //of the previous framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_DEPTH_TEST);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  sm_.program("screenShader")->useProgram();
  sm_.program("screenShader")->setUniform("postProcessingEffect", (unsigned int)State::postProcessingEffect_);
  glBindVertexArray(quadVAO); 
  glBindTexture(GL_TEXTURE_2D, texture);
  glDrawArrays(GL_TRIANGLES, 0, 6);
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

      if(physicsEngine_->getPickedModel() == it->second.second[i]){
        it->second.first.setUniform("picked", (unsigned int)1);
      }
      else{
        it->second.first.setUniform("picked", (unsigned int)0);
      }

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
  if(!State::cursorDisabled_){

    rayTo += btScalar(x) * dHor;
    rayTo -= btScalar(y) * dVert;
  }
  return rayDir;
}
