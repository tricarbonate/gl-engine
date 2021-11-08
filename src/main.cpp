#include "../include/Scene.h"
#include "../include/includes.h"

#include "../include/commonValues.hpp"
#include "../include/DataFormat.h"
#include "../include/EventHandler.h"
#include "../include/utils.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <stdlib.h>
#include <stdio.h>

const unsigned int WINDOW_HEIGHT = 1200;
const unsigned int WINDOW_WIDTH = 1600;

static float DELTA_TIME = 0.0f;
static float LAST_FRAME = 0.0f;

#define STRING(num) #num

int main(){

  /* WINDOW AND SCENE INITIALIZATION */
  initializeGlfw();
  
  //setup window properties:
  GLFWwindow* window;
  window = initializeWindow(WINDOW_HEIGHT, WINDOW_WIDTH);

  PhysicsEngine physicsEngine;
  initializeGlew(window);

  Assets::defineAssets();
  Scene scene = Scene(window, &physicsEngine);
  scene.setupScene();
  
  EventHandler eventHandler(window, scene.getCamera());

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSwapInterval(0);
  

      // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(NULL);

  /* MAIN LOOP */

  do{
      DELTA_TIME = getDeltaTime(LAST_FRAME);

      eventHandler.handleEvents(DELTA_TIME);

      glfwSetWindowSize(window, State::screenWidth_, State::screenHeight_);
      glViewport(0, 0, State::screenWidth_, State::screenHeight_);

      // feed inputs to dear imgui, start new frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();


      //printStateReport(DELTA_TIME, 200);
      scene.drawScene(DELTA_TIME);
      Model* pickedModel = physicsEngine.getPickedModel();

      // render your GUI
      ImGui::Begin("Demo window");
      if(pickedModel!=nullptr){
        std::string str = "X: " + std::to_string(pickedModel->getPosition().r) + " _Y: " +
          std::to_string(pickedModel->getPosition().g) + " _Z: " +
          std::to_string(pickedModel->getPosition().b);
        ImGui::Text(str.c_str());
      }

      ImGui::End();
      ImGui::Begin("Report Window");
      ImGui::Text(report(window, DELTA_TIME, 20).c_str());
      ImGui::End();

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(window);
      glfwPollEvents();
    } while(glfwWindowShouldClose(window) == 0 &&
           glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

  return 0;
}

