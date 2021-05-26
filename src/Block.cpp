#include "../include/Block.h"


Block::Block(Mesh* mesh, ShaderProgram* shaderProgram, glm::vec3 position):
  Model(mesh, "mainShader", shaderProgram, position)
{}
