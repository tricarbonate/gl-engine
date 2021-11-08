#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include "Light.h"

class SpotLight :
    public Light
{
    public: 
        SpotLight();
        SpotLight(glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f), 
            std::string mesh = "nullptr", ShaderProgram* shaderProgram = nullptr);
        ~SpotLight();

        private:

        glm::vec3 dir_;
};

#endif // __SPOT_LIGHT_H__
