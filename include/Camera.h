#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include <GLFW/glfw3.h>
//
#include "State.h"

class Camera {

  public:

    Camera();
    ~Camera();

    glm::mat4 lookAt();

    // getters
    glm::vec3 getPos() { return pos_; }
    float getSpeed() { return speed_; }
    glm::vec3 getFront() { return front_; }
    glm::vec3 getDirection() { return dir_; }
    glm::vec3 getRight() { return right_; }
    glm::vec3 getUp() { return up_; }

    double getYaw() { return yaw_; }
    double getPitch() { return pitch_; }

    // setters
    void setPos(glm::vec3 pos) {pos_ = pos;}
    void setYaw(double yaw) { yaw_ = yaw; } 
    void setPitch(double pitch) { pitch_ = pitch; }
    void setFirstMouse(bool firstMouse) { firstMouse_ = firstMouse; }

    void goForward(float deltaTime);
    void goBackward(float deltaTime);
    void goLeft(float deltaTime);
    void goRight(float deltaTime);
    void goUpward();
    void goDownward(float deltaTime);

    void updateOrientation(double xpos, double ypos, bool constrainPitch = true);
    void resetLastMousePos();

    void applyPhysics(float deltaTime, const float baseHeight);

  private:

    glm::vec3 pos_;
    glm::vec3 tar_;
    glm::vec3 dir_;
    glm::vec3 front_;
    glm::vec3 right_;
    glm::vec3 up_;

    double yaw_;
    double pitch_;

    bool firstMouse_;
    double lastX_, lastY_;

    const float speed_;
    double currentSpeed_;
    double acceleration_;

    unsigned int jumpCounter_;
};

//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

#endif // __CAMERA_H__ 
