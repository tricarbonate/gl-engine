#include "../include/ShaderManager.h"

ShaderManager::ShaderManager(){

}

ShaderManager::ShaderManager(const std::vector<ShaderSchema>& shaders)
{
    for(size_t i = 0; i < shaders.size(); i++){
        std::cout << "New shader" << std::endl;
        shaders_[shaders[i].first] = {
            ShaderProgram(shaders[i].second),
            std::vector<Model*>()
        }; 

        shaders_[shaders[i].first].first.compileProgram();

        //Assets::shaderPrograms[shaders[i].first] = &shaders_[shaders[i].first].first; 
    }
}

ShaderManager::~ShaderManager(){

}

void ShaderManager::bindToModels(std::vector<Model>& models){
    for(size_t i = 0; i < models.size(); i++){
        shaders_.at(models[i].getShaderProgram().first).second.push_back(&models[i]);
    }
}

void ShaderManager::bindToModel(Model& model){
    shaders_.at(model.getShaderProgram().first).second.push_back(&model);
}

unsigned int ShaderManager::getNumberOfModel(std::string shaderName){
    return shaders_.at(shaderName).second.size();
}

