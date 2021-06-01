#include "../include/Assets.h"

template<> Assets * Singleton<Assets>::instance_ = 0;

/* ASSETS DEFINITION */
std::unordered_map<std::string, Texture> Assets::textures = std::unordered_map<std::string, Texture>();
std::unordered_map<std::string, Material> Assets::materials = std::unordered_map<std::string, Material>();
std::unordered_map<std::string, Mesh> Assets::meshes = std::unordered_map<std::string, Mesh>();

std::unordered_map<std::string, ShaderProgram*> Assets::shaderPrograms = std::unordered_map<std::string, ShaderProgram*>();

std::vector<ShaderSchema> Assets::shaders;


/* ASSETS DEFINITION */
void Assets::defineAssets(){
    
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

  Assets::meshes["screenQuad"] = Mesh(DataFormat::getVerticesFromArray(quad, 6), Material(),
          std::vector<GLuint>());

  Assets::shaders.push_back({"mainShader", {
      {SHADERPROGRAM_VERT_LOC, GL_VERTEX_SHADER}, {SHADERPROGRAM_FRAG_LOC, GL_FRAGMENT_SHADER}}});
  Assets::shaders.push_back({"lightingShader",{
      {LIGHTINGSHADER_VERT_LOC, GL_VERTEX_SHADER}, {LIGHTINGSHADER_FRAG_LOC, GL_FRAGMENT_SHADER}
      }});
  Assets::shaders.push_back({"terrain_flatshader", {
      {TERRAIN_FLATSHADER_VERT_LOC, GL_VERTEX_SHADER}, {TERRAIN_FLATSHADER_FRAG_LOC, GL_FRAGMENT_SHADER}
      }});
  Assets::shaders.push_back({"screenShader", {
      {SCREEN_SHADER_VERT_LOC, GL_VERTEX_SHADER}, {SCREEN_SHADER_FRAG_LOC, GL_FRAGMENT_SHADER}
          }});
}



