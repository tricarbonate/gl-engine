#ifndef __SHADER_MANAGER_H__
#define __SHADER_MANAGER_H__

#include "ShaderProgram.h"
#include "Model.h"

#include <unordered_map>
#include <vector>
#include <string>

/* 
 * This struct is used for Shader Programs initializations
 */

/* This class contains all the shader programs available and links them to their
 * corresponding models.
 */
class ShaderManager {
  public:
    //default constructor
    ShaderManager(); 

    ShaderManager(std::vector<ShaderSchema> shaders);
    
    ~ShaderManager();

    void bindToModels(std::vector<Model>& models);

    auto& getShaders() { return shaders_; }
    auto at(std::string name) { return shaders_.at(name); }
    auto models(std::string name) { return shaders_.at(name).second; }
    ShaderProgram* program(std::string name) { return &shaders_.at(name).first; }

  private:
    
    // All shader programs mapped by name 
    // and bound to a std::vector of their corresponding models
    std::unordered_map<std::string, std::pair<ShaderProgram, std::vector<Model*> > > shaders_;    
};

#endif // __SHADER_MANAGER_H__
