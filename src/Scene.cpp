#include "../include/Scene.h"

Scene::Scene():
  models_(std::vector<Model>())
{
  //initialize shader programs
  std::vector<ShaderSchema> list = {
    {
      "mainShader",
      {
        {SHADERPROGRAM_VERT_LOC, GL_VERTEX_SHADER},
        {SHADERPROGRAM_FRAG_LOC, GL_FRAGMENT_SHADER}
      }
    },
    {
      "lightingShader",
      {
        {LIGHTINGSHADER_VERT_LOC, GL_VERTEX_SHADER},
        {LIGHTINGSHADER_FRAG_LOC, GL_FRAGMENT_SHADER}
      }
    },
    {
      "terrain_flatShader",
      {
        {TERRAIN_FLATSHADER_VERT_LOC, GL_VERTEX_SHADER},
        {TERRAIN_FLATSHADER_FRAG_LOC, GL_FRAGMENT_SHADER}
      }
    },
    {
      "AABB_baseShader",
      {
        {AABB_BASESHADER_VERT_LOC, GL_VERTEX_SHADER},
        {AABB_BASESHADER_FRAG_LOC, GL_FRAGMENT_SHADER}
      }
    }
  };
  sm_ = ShaderManager(list);
}

Scene::~Scene(){}

void Scene::defineTextures(){
  textures_["container"] = Texture(CONTAINER2_TEX_LOC);
  textures_["container_specular"] = Texture(CONTAINER2_SPEC_LOC);
  textures_["grass"] = Texture(GRASS_TEX_LOC, GL_RGB);
}

void Scene::defineMaterials(){
  materials_["container"] = {&textures_.at("container"),
    &textures_.at("container_specular"), nullptr, nullptr, 32.0f};
  materials_["grass"] = {&textures_.at("grass"),
    &textures_.at("container_specular"), nullptr, nullptr, 32.0f};
}

void Scene::defineMeshes(){
  meshes_["container"] = Mesh(getVerticesFromArray(vertices, 36), 
      materials_.at("container"), std::vector<GLuint>());

  meshes_["instancedContainer"] = Mesh(getVerticesFromArray(vertices, 36),
      materials_.at("container"), std::vector<GLuint>());

  meshes_["point_light"] = Mesh();
  meshes_["point_light"].createMesh(lightVertices, indices, 48, 36);

  meshes_["theiere"] = Mesh(getVerticesFromArrayAndNormals(gTheiereSommets, gTheiereNormales, 530),
      materials_.at("container"), std::vector<GLuint>(std::begin(gTheiereConnec), std::end(gTheiereConnec)));

  meshes_["grass"] = Mesh(getVerticesFromArray(groundVertices, 6),
      materials_.at("grass"), std::vector<GLuint>());
}

void Scene::setupScene(){

  defineTextures();
  defineMaterials();
  defineMeshes();

  for(unsigned int i = 0; i < 10; i ++){
    models_.push_back(Model(&meshes_.at("container"), "mainShader", sm_.program("mainShader"),
          glm::vec3(5 * cos(i), 2.0f, 5 * sin(i))));
    models_.back().getBoundingShape()->constructFromVertices(meshes_["container"].getVertices());
  }
  
  //theire model 
  for(unsigned int i = 0; i < 1; i++){
    models_.push_back(Model(&meshes_.at("theiere"), "mainShader", sm_.program("mainShader"),
          glm::vec3(15.0f * cos(i), i, 15.0f * sin(i))));
    models_.back().getBoundingShape()->constructFromVertices(meshes_["theiere"].getVertices());
  }

  // mirror
  mirrors_.push_back(Mirror(&meshes_.at("container"), sm_.program("mainShader"),
        glm::vec3(10.0f, 4.0f, 10.0f)));

  /* Initialization of lights */
  lights_ = {
    Light(LightType::DIRECTIONAL, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(),
        glm::vec3(-0.1f, -1.0f, 0.0f)),
    Light(LightType::POINT, glm::vec3(0.8f, 0.8f, 0.8f),
        glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(), &meshes_.at("point_light")),
    Light(LightType::POINT, glm::vec3(0.9f, 0.4f, 0.4f),
        glm::vec3(-1.0f, 3.0f, 0.0f), glm::vec3(), &meshes_.at("point_light")),
    Light(LightType::POINT, glm::vec3(0.4f, 0.9f, 0.0f),
        glm::vec3(0.0f, 6.0f, 0.0f), glm::vec3(), &meshes_.at("point_light")),
    Light(LightType::POINT, glm::vec3(0.1f, 0.1f, 0.8f),
        glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(), &meshes_.at("point_light"))
  }; 
  
  sm_.bindToModels(models_);
}


void Scene::drawScene(float deltaTime){

  deltaTime_ = deltaTime;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

  test_ += 0.01;
  for(size_t i = 0; i < lights_.size(); i++){
    glm::vec3 curr = lights_[i].getPosition();
    lights_[i].setPosition(curr.x + cos(test_ + (float)(i + 1)) / 20, curr.y, curr.z + sin(test_ + (float)(i+1)) / 20);
  }

  drawEntities();
  drawLights();
  drawTerrain();
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
      it->second.second[i]->accelerate(glm::vec3(cos(test_ * i / 2) / 8, GRAVITY_ACCELERATION * deltaTime_, 0.0f));
      it->second.second[i]->updatePosition(deltaTime_);
      modelMatrix_ = glm::translate(modelMatrix_, it->second.second[i]->getPosition());

      modelMatrix_ = glm::rotate(modelMatrix_, it->second.second[i]->getOrientation().r, glm::vec3(1, 0, 0));
      modelMatrix_ = glm::rotate(modelMatrix_, it->second.second[i]->getOrientation().g, glm::vec3(0, 1, 0));
      modelMatrix_ = glm::rotate(modelMatrix_, it->second.second[i]->getOrientation().b, glm::vec3(0, 0, 1));

      mvp_ = projectionMatrix_ * viewMatrix_ * modelMatrix_;
      it->second.first.setUniform("mvp", mvp_);
      it->second.first.setUniform("model", modelMatrix_);
      it->second.second[i]->draw();

      sm_.at("AABB_baseShader").first.useProgram();
      it->second.second[i]->drawBoundingVolume();

      checkForCollision();
    }
  }
}

void Scene::drawTerrain(){
  sm_.program("terrain_flatShader")->useProgram();  
  sm_.program("terrain_flatShader")->setUniform("viewPos", camera_.getPos());
  sm_.program("terrain_flatShader")->setUniformLights(lights_);

  terrain_.draw(modelMatrix_, viewMatrix_, projectionMatrix_, *sm_.program("terrain_flatShader"));
}


// TODO
void Scene::drawMirrors(){
    /* 1- 
     * the stencil test never passes, nothing is drawn, but stencil 
     * takes 1s at the mirrors position
     */
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NEVER, 1, 1);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    mirrors_[0].draw();
    glDisable(GL_CULL_FACE);

    /* 2-
     * Draws the reflected content of the mirror :
     */
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        glm::translate(modelMatrix_, glm::vec3(2.0f, 0.0f, 0.0f));
        glm::scale(modelMatrix_, glm::vec3(-1.0, 1.0, 1.0));
        glm::translate(modelMatrix_, glm::vec3(-2.0f, 0.0f, 0.0f));
    this->drawScene(deltaTime_);
    glDisable(GL_STENCIL_TEST);


    /* 3-
     * Draw the mirror as a transparent glass
     */
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    mirrors_[0].draw();
    //glDisable(GL_BLEND);    
}

//TODO mettre a jour les min et max quand on translate un Model
void Scene::checkForCollision(){
  for(size_t i = 0; i < models_.size() - 1; i++){
    for(size_t j = i + 1; j < models_.size(); j++){
      if(models_[i].getBoundingShape()->getMax().r < models_[j].getBoundingShape()->getMin().r ||
          models_[i].getBoundingShape()->getMin().r > models_[j].getBoundingShape()->getMax().r){
        //no collision
      }
      else if(models_[i].getBoundingShape()->getMax().g < models_[j].getBoundingShape()->getMin().g ||
          models_[i].getBoundingShape()->getMin().g > models_[j].getBoundingShape()->getMax().g){
        //no collision
      }
      else if(models_[i].getBoundingShape()->getMax().b < models_[j].getBoundingShape()->getMin().b ||
          models_[i].getBoundingShape()->getMin().b > models_[j].getBoundingShape()->getMax().b){
        //no collision
      }

      else{
        //only then we have a collision:
        //std::cout << "collision between " << i << " and " << j << std::endl;
      }
    }
  }
}
