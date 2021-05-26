#include "../include/ShaderManager.h"

ShaderManager::ShaderManager(){

}

ShaderManager::ShaderManager(std::vector<ShaderSchema> shaders)
{
    for(size_t i = 0; i < shaders.size(); i++){
        shaders_[shaders[i].name] = {
            ShaderProgram(shaders[i].files),
            std::vector<Model*>()
        }; 

        shaders_[shaders[i].name].first.compileProgram();
    }
}

void ShaderManager::bindToModels(std::vector<Model>& models){
    for(size_t i = 0; i < models.size(); i++){
        shaders_.at(models[i].getShaderProgram().first).second.push_back(&models[i]);
    }
}

ShaderManager::~ShaderManager(){

}
