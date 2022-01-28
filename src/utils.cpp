#include "../include/utils.hpp"

int failed(std::string message){
  std::cout << message << std::endl;
  glfwTerminate();
  return 1;
}

double getDeltaTime(float &lastFrame){
  float currentFrame = (float)glfwGetTime();
  float deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;
  return deltaTime;
}

template<class T>
void setOneTime(T& variable, T defaultValue, T newValue) {
    if (variable == defaultValue) {
        variable = newValue;
    }
    else {
        variable = defaultValue;
    }
}

void printMSperFrame(double deltaTime){
}

void printStateReport(GLFWwindow* window, double deltaTime, int nFrames){
  /* PRINTS ms/frames */
  static double deltaCount;
  static double frameCount;
  deltaCount += deltaTime;
  frameCount++;
  // prints every nframes frames
  if(frameCount >= nFrames){
    std::cout << "--REPORT--" << std::endl;
    std::cout << double(deltaCount / nFrames) * 1000 << " ms/frame" << std::endl;
    std::string str = State::picking_ == true ? "YES" : "NO";
    std::cout << "Currently picking : " << str << std::endl;
    deltaCount = 0;
    frameCount = 0;
    std::cout << std::endl;
  }
}

std::string report(GLFWwindow* window, double deltaTime, int nFrames){
  static std::string finalStr = "";
  static double deltaCount;
  static int frameCount;
  frameCount++;
  deltaCount += deltaTime;
  if(frameCount >= nFrames){
    finalStr = "";
    finalStr += std::to_string(double(deltaCount / nFrames) * 1000) + " ms/frame\n";
    std::string isPicking = State::picking_ == true ? "YES" : "NO";
    std::string flatShading = State::terrainFlatShading_ == true ? "YES" : "NO";
    GLdouble xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    finalStr += "Currently picking : " + isPicking + "\n";
    finalStr += "Using Flat Shading : " + flatShading + "\n";
    finalStr += "Cursor:   X: " + std::to_string(xpos) + " | Y: " + std::to_string(ypos) + "\n";
    deltaCount = 0;
    frameCount = 0;
  }


  return finalStr;
}

GLFWwindow* initializeWindow(const unsigned int windowHeight, const unsigned int windowWidth){

  //glfwWindowHint(GLFW_SAMPLES, 4);

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

glm::vec3 randomVec3(double min, double max, glm::vec3 xyz){
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(min, max);

  double x, y, z;
  if(xyz.r == 1)
    x = distr(eng);
  else
    x = 1;
  if(xyz.y == 1)
    y = distr(eng);
  else
    y = 1;
  if(xyz.b == 1)
    z = distr(eng);
  else
    z = 1;
  return glm::vec3(x, y, z);
}

