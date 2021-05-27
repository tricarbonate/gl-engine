#include "../include/Quad.h"

Quad::Quad(Mesh* mesh, ShaderProgram* shaderProgram, glm::vec3 position):
    Model(mesh, "mainshader", shaderProgram, position)
{

}

