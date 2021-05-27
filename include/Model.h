#ifndef MODEL_H
#define MODEL_H

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"

#include <bullet/btBulletDynamicsCommon.h>

enum COLLISION_SHAPES{
  CUBE,
  SPHERE
};

class Model {

  public:
    Model();
    Model(Mesh* mesh, const char* shaderName, ShaderProgram* shaderProgram,
        glm::vec3 position);
    
    void draw();

    std::pair<const char*, ShaderProgram*> getShaderProgram() const { return shaderProgram_; }
    
    // getters
    Mesh* getMesh() { return mesh_; }
    glm::vec3 getPosition() { return position_; }
    glm::vec3 getOrientation() { return orientation_; }

    // setters
    void setPosition(glm::vec3 position) { position_ = position; }

    void setOrientation(glm::vec3 orientation) {orientation_ = orientation;}

    //void accelerate(glm::vec3 acceleration);

    void updatePosition(btTransform trans);

    void initPhysics(btDiscreteDynamicsWorld* dynamicsWorld, COLLISION_SHAPES shape, double data = 0.5);

    void setTransform(btTransform trans) { trans_ = trans; }

    btRigidBody* getRigidBody() { return body_; }

  private:
    // pointer to the mesh representing the model
    Mesh* mesh_;
    
    // pointer to the shader program
    // used to render the model:
    std::pair<const char*, ShaderProgram*> shaderProgram_;
    
    glm::vec<3, double, glm::defaultp> position_;
    glm::vec<3, double, glm::defaultp> orientation_; // object orientation on its axis
    glm::vec<3, double, glm::defaultp> currentSpeed_;

    btCollisionShape* collisionShape_;
    btRigidBody* body_;
    btTransform trans_;
};

#endif // MODEL_H
