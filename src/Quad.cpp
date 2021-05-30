#include "../include/Quad.h"

Quad::Quad(std::string mesh, ShaderProgram* shaderProgram, glm::vec3 position):
    Model(mesh, "mainshader", shaderProgram, position)
{

}

