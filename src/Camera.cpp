#include "../include/Camera.h"

Camera::Camera():
  pos_(glm::vec3(-10.0f, -3.0f, 15.0f)),
  tar_(glm::vec3(0.0f, 0.0f, 0.0f)),
  dir_(glm::normalize(pos_ - tar_)),
  front_(dir_),
  right_(glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), dir_))),
  up_(glm::cross(dir_, right_)),
  yaw_(atan2(dir_.x, dir_.z)),
  pitch_(asin(-dir_.y)),
  firstMouse_(true),
  lastX_(State::screenWidth_ / 2),
  lastY_(State::screenHeight_ / 2),
  speed_(10.5f)
{

}

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

void Camera::resetLastMousePos(){
  lastX_ = State::screenWidth_ / 2;
  lastY_ = State::screenHeight_ / 2;
}

void updateCameraVectors(){
  //disabled pitch and yaw constraint
}

void Camera::updateOrientation(double xpos, double ypos, bool constrainPitch)
{
  if(firstMouse_)
  {
      lastX_ = xpos;
      lastY_ = ypos;
      firstMouse_ = false;
      std::cout << "first Mouse" << std::endl;
      return;
  }

  double xoffset = xpos - lastX_;
  double yoffset = lastY_ - ypos;
  lastX_ = xpos;
  lastY_ = ypos;

  double sensitivity = 0.05;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw_   += xoffset;
  pitch_ += yoffset;

  if(constrainPitch){
    if(pitch_ > 89.0f)
        pitch_ = 89.0f;
    if(pitch_ < -89.0f)
        pitch_ = -89.0f;
  }

  glm::vec3 direction;
  direction.x = (float)(cos(glm::radians(yaw_)) * cos(glm::radians(pitch_)));
  direction.y = (float)(sin(glm::radians(pitch_)));
  direction.z = (float)(sin(glm::radians(yaw_)) * cos(glm::radians(pitch_)));
  front_ = glm::normalize(direction);
  right_ = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), front_));
  up_ = glm::normalize(glm::cross(front_, right_));
}

