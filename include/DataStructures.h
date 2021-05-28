#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

#include "Texture.h"

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <vector>
#include <unordered_map>

struct Vertex{
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoords;
};

//Material contains textures for diffuse maps
// specular maps, normal maps, height maps
// and a shininess factor
struct Material{
  Texture* diffuse;
  Texture* specular;
  Texture* normal;
  Texture* height;
  float shininess;
};

typedef std::pair<std::string, std::vector<std::pair<const char*, GLenum>>> ShaderSchema;

#endif // __DATA_STRUCTURES_H__
