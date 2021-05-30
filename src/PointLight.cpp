#include "../include/PointLight.h"


PointLight::PointLight(){}

PointLight::PointLight(glm::vec3 color, 
        glm::vec3 position, 
        glm::vec3 direction, 
        Mesh* mesh, ShaderProgram* shaderProgram) :
    Light(LightType::POINT, color, position, direction, mesh, shaderProgram)
{

}

PointLight::~PointLight(){}



