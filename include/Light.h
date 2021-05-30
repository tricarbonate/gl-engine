#ifndef LIGHT_H
#define LIGHT_H

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"

enum class LightType{
  DIRECTIONAL,
  POINT,
  SPOT
};

class Light : public Model {
  public:
    Light();
    Light(LightType type, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f), 
        Mesh* mesh = nullptr, ShaderProgram* shaderProgram = nullptr);
    ~Light();

    void draw();

    void setAmbientColor(float r, float g, float b); 
    void setDiffuseColor(float r, float g, float b);
    void setSpecularColor(float r, float g, float b);
    void setDirection(float x, float y, float z);
    void setIntensity(double intensity);

    LightType getType() const { return lightType_; }
    glm::vec3 getAmbientColor() const { return ambientColor_; }
    glm::vec3 getDiffuseColor() const { return diffuseColor_; }
    glm::vec3 getSpecularColor() const { return specularColor_; }
    glm::vec3 getDirection() const { return direction_; }
    double getIntensity() const { return intensity_; }
    
  protected:
    LightType lightType_;

    glm::vec3 ambientColor_, diffuseColor_, specularColor_;
    glm::vec3 direction_;

    double intensity_;
};

#endif //LIGHT
