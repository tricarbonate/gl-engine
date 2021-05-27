#include "../include/utils.hpp"

int failed(std::string message){
  std::cout << message << std::endl;
  glfwTerminate();
  return 1;
}


float getDeltaTime(float &lastFrame){
  float currentFrame= (float)glfwGetTime();
  float deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;
  return deltaTime;
}

void printMSperFrame(double deltaTime){
  static double deltaCount;
  static double frameCount;
  deltaCount += deltaTime;
  frameCount++;
  // prints every 200 frames
  if(frameCount >= 200){
    std::cout << double(deltaCount / 200) * 1000 << " ms/frame" << std::endl;
    deltaCount = 0;
    frameCount = 0;
  }
}

GLFWwindow* initializeWindow(const unsigned int windowHeight, const unsigned int windowWidth){ 

  GLFWwindow *window = glfwCreateWindow(windowWidth, // window width
      windowHeight, // window height
      "test", // window title
      NULL,
      NULL);

  glfwMakeContextCurrent(window); // define the context.
  return window;
}


int initializeGlew(GLFWwindow *window){
  if(glewInit() != GLEW_OK){
    glfwDestroyWindow(window);
    return failed("failed to initialize glew");
  }

  glewExperimental = true;
  glEnable(GL_DEPTH_TEST);
  /* glEnable(GL_CULL_FACE); */
  return 0;
}



int initializeGlfw(){
  //initialize glfw:
  if(!glfwInit()){
    return failed("failed to initialize GLFW");
  }

  //setting opengl version:
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 

  return 0;
}
