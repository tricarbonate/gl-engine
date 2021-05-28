#include "../include/Assets.h"

template<> Assets * Singleton<Assets>::instance_ = 0;

/* ASSETS DEFINITION */
std::unordered_map<std::string, Texture> Assets::textures = std::unordered_map<std::string, Texture>();
std::unordered_map<std::string, Material> Assets::materials = std::unordered_map<std::string, Material>();
std::unordered_map<std::string, Mesh> Assets::meshes = std::unordered_map<std::string, Mesh>();
std::vector<ShaderSchema> Assets::shaders;





