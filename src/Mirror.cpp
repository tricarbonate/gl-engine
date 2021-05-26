#include "../include/Mirror.h"


Mirror::Mirror(Mesh* mesh, ShaderProgram* shaderProgram, glm::vec3 position):
    Model(mesh, "mainShader", shaderProgram, position)
{}

Mirror::Mirror() {}

Mirror::~Mirror(){}
