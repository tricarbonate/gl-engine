#include "../include/Light.h"

Light::Light(){}

Light::Light(LightType type, glm::vec3 color, glm::vec3 position,
    glm::vec3 direction, std::string mesh, ShaderProgram* shaderProgram):
  Model(mesh, "lightingShader", shaderProgram, position),
  lightType_(type),
  diffuseColor_(color),
  specularColor_(color),
  direction_(direction),
  intensity_(1)
{
  ambientColor_ = glm::vec3(0.2f, 0.2f, 0.2f);
}

Light::~Light(){
}

void Light::draw(){
  this->mesh_->renderMesh();
}

void Light::setDirection(float x, float y, float z){
  direction_ = glm::vec3(x, y, z);
}

void Light::setAmbientColor(float r, float g, float b){
  ambientColor_ = glm::vec3(r, g, b);
}

void Light::setDiffuseColor(float r, float g, float b){
  diffuseColor_ = glm::vec3(r, g, b);
}

void Light::setSpecularColor(float r, float g, float b){
  specularColor_ = glm::vec3(r, g, b);
}
