#include "../include/SpotLight.h"

SpotLight::SpotLight() {}

SpotLight::SpotLight(glm::vec3 color,
        glm::vec3 position,
        glm::vec3 direction,
        std::string mesh, ShaderProgram* shaderProgram) :
    Light(LightType::SPOT, color, position, direction, mesh, shaderProgram)
{

}

SpotLight::~SpotLight() {}
