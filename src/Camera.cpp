#include "../include/Camera.h"

Camera::Camera():
  pos_(glm::vec3(0.0f, 0.0f, 3.0f)),
  tar_(glm::vec3(0.0f, 0.0f, 0.0f)),
  dir_(glm::normalize(pos_ - tar_)),
  front_(glm::vec3(0.0f, 0.0f, -1.0f)),
  right_(glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), dir_))),
  up_(glm::cross(dir_, right_)),
  speed_(10.5f),
  yaw_(-90.0f),
  pitch_(0.0f)
{}

Camera::~Camera(){}


void Camera::goForward(float deltaTime){
  this->pos_ += speed_ * deltaTime * front_;
}
void Camera::goBackward(float deltaTime){
  this->pos_ -= speed_ * deltaTime * front_;
}
void Camera::goLeft(float deltaTime){
  this->pos_ -= normalize(glm::cross(front_, up_)) * speed_ * deltaTime;
}
void Camera::goRight(float deltaTime){
  this->pos_ += normalize(glm::cross(front_, up_)) * speed_ * deltaTime;
}
void Camera::goUpward(float deltaTime){
  this->pos_ += glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime * speed_;
}
void Camera::goDownward(float deltaTime){
  this->pos_ -= glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime * speed_;
}

glm::mat4 Camera::lookAt(){
  return glm::lookAt(
      pos_,
      pos_ + front_,
      up_);
}


void Camera::updateOrientation(double xpos, double ypos)
{
  if(firstMouse)
  {
      lastX = xpos;
      lastY = ypos;
      firstMouse = false;
  }

  double xoffset = xpos - lastX;
  double yoffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;

  double sensitivity = 0.05;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw_   += xoffset;
  pitch_ += yoffset;

  if(pitch_ > 89.0f)
      pitch_ = 89.0f;
  if(pitch_ < -89.0f)
      pitch_ = -89.0f;

  glm::vec3 direction;
  direction.x = (float)(cos(glm::radians(yaw_)) * cos(glm::radians(pitch_)));
  direction.y = (float)(sin(glm::radians(pitch_)));
  direction.z = (float)(sin(glm::radians(yaw_)) * cos(glm::radians(pitch_)));
  front_ = glm::normalize(direction);
}

