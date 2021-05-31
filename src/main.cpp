#include "../include/Scene.h"
#include "../include/includes.h"

#include "../include/commonValues.hpp"
#include "../include/DataFormat.h"
#include "../include/EventHandler.h"
#include "../include/utils.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

const unsigned int WINDOW_HEIGHT = 1200;
const unsigned int WINDOW_WIDTH = 1600;

static float DELTA_TIME = 0.0f;
static float LAST_FRAME = 0.0f;

/* ASSETS DEFINITION */
void defineAssets(){
  Assets::textures["container"] = Texture(CONTAINER2_TEX_LOC);
  Assets::textures["container_specular"] = Texture(CONTAINER2_SPEC_LOC);
  Assets::textures["grass"] = Texture(GRASS_TEX_LOC, GL_RGB);

  Assets::materials["container"] = {&Assets::textures.at("container"),
    &Assets::textures.at("container_specular"), nullptr, nullptr, 32.0f};
  Assets::materials["grass"] = {&Assets::textures.at("grass"),
    &Assets::textures.at("container_specular"), nullptr, nullptr, 32.0f};

  Assets::meshes["container"] = Mesh(DataFormat::getVerticesFromArray(vertices, 36), 
      Assets::materials.at("container"), std::vector<GLuint>());

  Assets::meshes["instancedContainer"] = Mesh(DataFormat::getVerticesFromArray(vertices, 36),
      Assets::materials.at("container"), std::vector<GLuint>());

  Assets::meshes["point_light"] = Mesh();
  Assets::meshes["point_light"].createMesh(lightVertices, indices, 48, 36);


  Assets::meshes["theiere"] = 
    Mesh(DataFormat::getVerticesFromArrayAndNormals(gTheiereSommets, gTheiereNormales, 530),
      Assets::materials.at("container"),
      std::vector<GLuint>(std::begin(gTheiereConnec), std::end(gTheiereConnec)));

  Assets::meshes["grass"] = Mesh(DataFormat::getVerticesFromArray(groundVertices, 6),
      Assets::materials.at("grass"), std::vector<GLuint>());

  Assets::shaders.push_back({"mainShader", {
      {SHADERPROGRAM_VERT_LOC, GL_VERTEX_SHADER}, {SHADERPROGRAM_FRAG_LOC, GL_FRAGMENT_SHADER}}});
  Assets::shaders.push_back({"lightingShader",{
      {LIGHTINGSHADER_VERT_LOC, GL_VERTEX_SHADER}, {LIGHTINGSHADER_FRAG_LOC, GL_FRAGMENT_SHADER}
      }});
  Assets::shaders.push_back({"terrain_flatshader", {
      {TERRAIN_FLATSHADER_VERT_LOC, GL_VERTEX_SHADER}, {TERRAIN_FLATSHADER_FRAG_LOC, GL_FRAGMENT_SHADER}
      }});
}


int main(){

  /* WINDOW AND SCENE INITIALIZATION */
  initializeGlfw();
  
  //setup window properties:
  GLFWwindow* window;
  window = initializeWindow(WINDOW_HEIGHT, WINDOW_WIDTH);

  initializeGlew(window);

  defineAssets();
  Scene scene = Scene(window);
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

