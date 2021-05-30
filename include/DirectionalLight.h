#ifndef __DIRECTIONAL_LIGHT_H__
#define __DIRECTIONAL_LIGHT_H__


#include "Light.h"


class DirectionalLight : 
  public Light
{
  public:
    DirectionalLight();
    //directional lights don't need a position or 
    DirectionalLight(glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f));
    ~DirectionalLight();


  private:
    
};

#endif // __DIRECTIONAL_LIGHT_H__
