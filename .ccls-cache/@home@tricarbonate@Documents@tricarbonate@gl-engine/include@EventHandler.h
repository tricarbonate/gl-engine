#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "GLFW/glfw3.h"
#include "State.h"
#include "Camera.h"

class EventHandler{
  public:
    EventHandler(GLFWwindow* window, Camera* camera);
    ~EventHandler();

    void handleEvents(float deltaTime);

    static void resetLastMousePos();

  private:
  
    void handleKeys(float deltaTime);
    void handleMouse();

    bool pressed(int key);

    GLFWwindow* window_;
    Camera* camera_;

    bool releasedJump_;
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

#endif //__EVENT_HANDLER_H__ 
