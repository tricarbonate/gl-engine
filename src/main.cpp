#include "../include/Scene.h"

const unsigned int WINDOW_HEIGHT = 1200;
const unsigned int WINDOW_WIDTH = 1600;

static float DELTA_TIME = 0.0f;
static float LAST_FRAME = 0.0f;

int main(){

  /* WINDOW AND SCENE INITIALIZATION */
  initializeGlfw();
  
  //setup window properties:
  GLFWwindow* window;
  window = initializeWindow(WINDOW_HEIGHT, WINDOW_WIDTH);

  initializeGlew(window);

  Scene scene;
  scene.setupScene();
  
  EventHandler eventHandler(window, scene.getCamera());
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSwapInterval(0);
  

  /* MAIN LOOP */

  do{
      DELTA_TIME = getDeltaTime(LAST_FRAME);

      eventHandler.handleEvents(DELTA_TIME);
      if(State::fullScreenMode_){
        glfwSetWindowSize(window, 1920, 1080);
        glViewport(0, 0, 1920, 1080);
      }
      else{
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        glfwSetWindowSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);
      }

      printMSperFrame(DELTA_TIME);

      scene.drawScene(DELTA_TIME);

      glfwSwapBuffers(window);
      glfwPollEvents();

    }while(glfwWindowShouldClose(window) == 0 &&
           glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

  return 0;
}

