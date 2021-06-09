#include "../include/VoxModel.h"


VoxModel::VoxModel(){
    mesh_ = new Voxel();    
}

VoxModel::VoxModel(glm::vec3 position, const char* shaderName, ShaderProgram* shaderProgram):
    Model()
{
    position_ = position;
    shaderProgram_ = {shaderName, shaderProgram};
    mesh_ = new Voxel();
}

VoxModel::~VoxModel(){
    
}

void VoxModel::addVoxel(glm::vec3 at){
    positions_.push_back(at);
}

