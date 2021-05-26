#include "../include/Model.h"

Model::Model():
  mesh_(nullptr),
  position_(glm::vec3(0.0f, 0.0f, 0.0f)),
  orientation_(glm::vec3(0.0f, 0.0f, 0.0f)),
  currentSpeed_(glm::vec3(0.0f, 0.0f, 0.0f))
{}

Model::Model(Mesh* mesh, const char* shaderName, ShaderProgram* shaderProgram, glm::vec3 position):
  mesh_(mesh),
  shaderProgram_({shaderName, shaderProgram}),
  position_(position)
{}

void Model::draw(){
  glActiveTexture(GL_TEXTURE0);
  shaderProgram_.second->setUniform("material.diffuse", (unsigned int)0);
  mesh_->getMaterial().diffuse->bind();
  glActiveTexture(GL_TEXTURE0 + 1);
  shaderProgram_.second->setUniform("material.specular", (unsigned int)1);
  mesh_->getMaterial().diffuse->bind();
  shaderProgram_.second->setUniform("material.shininess", mesh_->getMaterial().shininess);
  glActiveTexture(GL_TEXTURE0);

  mesh_->renderMesh(*shaderProgram_.second, false);  
}

void Model::accelerate(glm::vec3 acceleration){
  this->currentSpeed_ += acceleration;
}


void Model::updatePosition(float deltaTime){
  this->position_ += currentSpeed_ * (double)deltaTime;
}
