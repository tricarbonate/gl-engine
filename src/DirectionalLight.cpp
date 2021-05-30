#include "../include/DirectionalLight.h"


DirectionalLight::DirectionalLight(){}

DirectionalLight::DirectionalLight(glm::vec3 color, 
    glm::vec3 direction) :
    Light(LightType::DIRECTIONAL, color, glm::vec3(), direction)
{
  ambientColor_ = glm::vec3(0.2f, 0.2f, 0.2f);
}

DirectionalLight::~DirectionalLight(){

}

