#ifndef __POINT_LIGHT_H__
#define __POINT_LIGHT_H__

#include "Light.h"


class PointLight :
  public Light
{
  public:
    PointLight();
    PointLight(glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f), 
        std::string mesh = "nullptr", ShaderProgram* shaderProgram = nullptr);
    ~PointLight();

  private:

};


#endif // __POINT_LIGHT_H__
