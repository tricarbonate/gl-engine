#ifndef __CAMERA_H__
#define __CAMERA_H__


#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include <GLFW/glfw3.h>

class Camera{

  public:

    Camera();
    ~Camera();

    glm::mat4 lookAt();

    // getters
    glm::vec3 getPos() { return pos_; }
    float getSpeed() { return speed_; }
    glm::vec3 getFront() { return front_; }

    // setters
    void setPos(glm::vec3 pos) {pos_ = pos;}

    void goForward(float deltaTime);
    void goBackward(float deltaTime);
    void goLeft(float deltaTime);
    void goRight(float deltaTime);
    void goUpward(float deltaTime);
    void goDownward(float deltaTime);

    void updateOrientation(double xpos, double ypos);

  private:

    glm::vec3 pos_;
    glm::vec3 tar_;
    glm::vec3 dir_;
    glm::vec3 front_;
    glm::vec3 right_;
    glm::vec3 up_;

    bool firstMouse = true;
    double lastX = 400, lastY = 300;

    const float speed_;

    double yaw_;
    double pitch_;

};

#endif // __CAMERA_H__ 
