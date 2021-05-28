#include "../include/Assets.h"

template <> Assets * Singleton<Assets>::instance_ = 0;

/* ASSETS DEFINITION */
std::unordered_map<std::string, Texture> textures = std::unordered_map<std::string, Texture>();
std::unordered_map<std::string, Material> materials = std::unordered_map<std::string, Material>();
std::unordered_map<std::string, Mesh> meshes = std::unordered_map<std::string, Mesh>();





