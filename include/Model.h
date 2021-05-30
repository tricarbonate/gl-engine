#ifndef __MODEL_H__
#define __MODEL_H__

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"

// Forward declaration of ShaderProgram to avoid recursive include of files
// Model class only need a reference to a ShaderProgram (in this file)
class ShaderProgram;

#include <btBulletDynamicsCommon.h>

enum COLLISION_SHAPES{
  CUBE,
  SPHERE,
  CONVEX_HULL,
  TRIANGLE_MESH
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
    btRigidBody* getRigidBody() { return body_; }
    glm::vec3 getPosition() const { return position_; }
    glm::vec3 getOrientation() { return orientation_; }

    // setters
    void setPosition(glm::vec3 position) { position_ = position; }
    void setOrientation(glm::vec3 orientation) {orientation_ = orientation;}
    void setConvexHullShape();
    void setTransform(btTransform trans) { trans_ = trans; }
    void setMesh(Mesh* mesh) { mesh_ = mesh; }

    void updatePosition(btTransform trans);

    void initPhysics(btDiscreteDynamicsWorld* dynamicsWorld, COLLISION_SHAPES shape, double data = 0.5);

  protected:
    // pointer to the mesh representing the model
    Mesh* mesh_;
    
    // pointer to the shader program
    // used to render the model:
    std::pair<const char*, ShaderProgram*> shaderProgram_;
    
    glm::vec<3, double, glm::defaultp> position_;
    glm::vec<3, double, glm::defaultp> orientation_; // object orientation on its axis
    glm::vec<3, double, glm::defaultp> currentSpeed_;
    glm::vec<3, double, glm::defaultp> acceleration_;

    btCollisionShape* collisionShape_;
    btRigidBody* body_;
    btTransform trans_;
};

#endif // MODEL_H
