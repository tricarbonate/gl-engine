#include "../include/Block.h"

Block::Block(std::string mesh, ShaderProgram* shaderProgram, glm::vec3 position):
  Model(mesh, "mainShader", shaderProgram, position)
{}
