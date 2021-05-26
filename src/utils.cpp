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

std::vector<Vertex> getVerticesFromArray(float* arr, unsigned int nVertices){
  std::vector<Vertex> v = std::vector<Vertex>();
  for(unsigned int i = 0; i < nVertices * 8; i += 8){
    Vertex vertex;
    vertex.position = glm::vec3(arr[i], arr[i + 1], arr[i + 2]);
    vertex.normal = glm::vec3(arr[i + 3], arr[i + 4], arr[i + 5]);
    vertex.texCoords = glm::vec2(arr[i + 6], arr[i + 7]);
    v.push_back(vertex);
  }
  return v;
}

std::vector<Vertex> getVerticesFromArrayAndNormals(float* vertices, float* normals, unsigned int nVertices){
  std::vector<Vertex> v = std::vector<Vertex>();
  for(unsigned int i = 0; i < nVertices * 3; i+=3){
    Vertex vertex;
    vertex.position = glm::vec3(vertices[i], vertices[i+1], vertices[i+2]);
    vertex.normal = glm::vec3(normals[i], normals[i+1], normals[i+2]);
    vertex.texCoords = glm::vec2(0.0f, 0.0f);
    v.push_back(vertex);
  }
  return v;
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
