#ifndef LIGHT_H
#define LIGHT_H

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Mesh;

enum class LightType{
  DIRECTIONAL,
  POINT,
  SPOT
};

class Light{
  public:
    Light();
    Light(LightType type, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f), 
        Mesh* mesh = nullptr);
    ~Light();



    void setPosition(float x, float y, float z);
    void setAmbientColor(float r, float g, float b); 
    void setDiffuseColor(float r, float g, float b);
    void setSpecularColor(float r, float g, float b);
    void setDirection(float x, float y, float z);
    void setMesh(Mesh* mesh) { mesh_ = mesh; }

    LightType getType() const { return lightType_; }
    glm::vec3 getPosition() const { return position_; }
    glm::vec3 getAmbientColor() const { return ambientColor_; }
    glm::vec3 getDiffuseColor() const { return diffuseColor_; }
    glm::vec3 getSpecularColor() const { return specularColor_; }
    glm::vec3 getDirection() const { return direction_; }
    Mesh* getMesh() const { return mesh_; }
    
  private:
    LightType lightType_;

    glm::vec3 position_; 
    glm::vec3 ambientColor_, diffuseColor_, specularColor_;
    glm::vec3 direction_;

    Mesh* mesh_;
};

#endif //LIGHT
