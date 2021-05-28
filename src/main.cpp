#define BT_USE_DOUBLE_PRECISION

#include "../include/Scene.h"

#include "../include/imgui.h"
#include "../include/imgui_impl_glfw.h"
#include "../include/imgui_impl_opengl3.h"

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
  

      // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  // Setup Platform/Renderer bindings
  //ImGui_ImplGlfw_InitForOpenGL(window, true);
  //ImGui_ImplOpenGL3_Init();
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();


  ImGui_ImplGlfw_InitForOpenGL(window, true);
  //ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(NULL);

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

      // feed inputs to dear imgui, start new frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      printMSperFrame(DELTA_TIME);
      scene.drawScene(DELTA_TIME);

            // render your GUI
      ImGui::Begin("Demo window");
      ImGui::Button("Hello!");
      ImGui::End();

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(window);
      glfwPollEvents();

    }while(glfwWindowShouldClose(window) == 0 &&
           glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

  return 0;
}

