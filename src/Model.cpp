#include "../include/Model.h"

Model::Model():
  mesh_(nullptr),
  position_(glm::vec3(0.0f, 0.0f, 0.0f)),
  orientation_(glm::vec3(0.0f, 0.0f, 0.0f)),
  currentSpeed_(glm::vec3(0.0f, 0.0f, 0.0f))
{}

Model::Model(Mesh* mesh, const char* shaderName, ShaderProgram* shaderProgram, glm::vec3 position):
  mesh_(mesh),
  shaderProgram_({shaderName, shaderProgram}),
  position_(position)
{}

void Model::draw(){
  glActiveTexture(GL_TEXTURE0);
  shaderProgram_.second->setUniform("material.diffuse", (unsigned int)0);
  mesh_->getMaterial().diffuse->bind();
  glActiveTexture(GL_TEXTURE0 + 1);
  shaderProgram_.second->setUniform("material.specular", (unsigned int)1);
  mesh_->getMaterial().diffuse->bind();
  shaderProgram_.second->setUniform("material.shininess", mesh_->getMaterial().shininess);
  glActiveTexture(GL_TEXTURE0);

  mesh_->renderMesh(*shaderProgram_.second, false);  
}

void Model::updatePosition(btTransform trans){
  position_.r = (double)trans.getOrigin().getX();
  position_.g = (double)trans.getOrigin().getY();
  position_.b = (double)trans.getOrigin().getZ();

  btScalar angles[3];
  trans.getRotation().getEulerZYX(angles[2], angles[1], angles[0]);
  orientation_.r = angles[0];
  orientation_.g = angles[1];
  orientation_.b = angles[2];

}

void Model::initPhysics(btDiscreteDynamicsWorld* dynamicsWorld, COLLISION_SHAPES shape, double data){
  if(shape == COLLISION_SHAPES::CUBE){
    collisionShape_ = new btBoxShape(btVector3(data, data, data));
  }
  else if (shape == COLLISION_SHAPES::SPHERE){
    collisionShape_ = new btSphereShape(btScalar(data));
  }
  
  btTransform startTransform;
  startTransform.setIdentity();
  btVector3 initialPosition = btVector3(position_.r, position_.g, position_.b);
  startTransform.setOrigin(initialPosition);
  
  btScalar mass(1.f);

  bool isDynamic = (mass != 0.f);
  btVector3 localInertia(0, 0, 0);
  if(isDynamic){
    collisionShape_->calculateLocalInertia(mass, localInertia);
  }

  btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, collisionShape_, localInertia);
  body_ = new btRigidBody(rbInfo);

  dynamicsWorld->addRigidBody(body_);
}
