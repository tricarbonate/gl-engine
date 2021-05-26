/* This file contains a simple shader program class 
 * all the files locations are stored in locs_ with their corresponding shader types
 * */

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <typeinfo> // used for setUniform()
#include <string>
#include <fstream>
#include <cstring>
#include <iostream>
#include <map>

#include "Light.h"

class ShaderProgram{
  public:

    ShaderProgram(); //cstr
    ShaderProgram(std::vector<std::pair<const char*, GLenum> > locations);
    ~ShaderProgram(); 

    // use glUseProgram(GLuint)
    void useProgram();

    // compile the shader program
    void compileProgram();

    // add a file with corresponding type to locs_
    void addFile(const char* fileLocation, GLenum shaderType);

    // two functions to set set the uniform variables:
    // the first one finds the id of uniformName and calls the second
    template<typename T>
    inline void setUniform(const char* uniformName, T value);
    
    // the second function call glUniformX() (with X being the right variable type):w
    template<typename T>
    inline void setUniform_part(GLuint id, T value);

    inline void setUniformLights(const std::vector<Light>& lights);
    
  private:
    GLuint shaderID_;

    //locs_ contains all files locations and their corresponding GLenum shader types.
    //the class will create the right number of shaders and compile them into one program
    std::vector<std::pair<const char*, GLenum> > locs_;
    
    // read shader file and returns formatted string
    std::string readFile(const char* fileLocation);
    
    //add a shader to the program
    void addShader(GLuint programID, const char* shaderCode, GLenum shaderType);
};


template<typename T>
inline void ShaderProgram::setUniform(const char* uniformName, T value){
  setUniform_part(glGetUniformLocation(shaderID_, uniformName), value);
}

template<>
inline void ShaderProgram::setUniform_part<float>(GLuint id, float value){
  glUniform1f(id, value);
}

template<>
inline void ShaderProgram::setUniform_part<glm::mat4>(GLuint id, glm::mat4 value){
  glUniformMatrix4fv(id, 1, GL_FALSE, &value[0][0]);
}

template<>
inline void ShaderProgram::setUniform_part<glm::vec3>(GLuint id, glm::vec3 value){
  glUniform3f(id, value.x, value.y, value.z);
}

template<>
inline void ShaderProgram::setUniform_part<unsigned int>(GLuint id, unsigned int value){
  glUniform1i(id, value);
}


inline void ShaderProgram::setUniformLights(const std::vector<Light>& lights)
{
  unsigned int pointLightCount = 0;
  for(unsigned int i = 0; i < lights.size(); i++){
    switch(lights[i].getType()){
      case LightType::DIRECTIONAL:
        setUniform("dirLight.direction", lights[i].getDirection());
        setUniform("dirLight.ambient", lights[i].getAmbientColor());
        setUniform("dirLight.diffuse", lights[i].getDiffuseColor());
        setUniform("dirLight.specular", lights[i].getSpecularColor());
        break;

      case LightType::POINT:
        char buffer[64];

        sprintf(buffer, "pointLights[%i].position", pointLightCount);
        setUniform(buffer, lights[i].getPosition());

        sprintf(buffer, "pointLights[%i].ambient", pointLightCount);
        setUniform(buffer, lights[i].getAmbientColor());

        sprintf(buffer, "pointLights[%i].diffuse", pointLightCount);
        setUniform(buffer, lights[i].getDiffuseColor());
        
        sprintf(buffer, "pointLights[%i].specular", pointLightCount);
        setUniform(buffer, lights[i].getSpecularColor());

        sprintf(buffer, "pointLights[%i].constant", pointLightCount);
        setUniform(buffer, 1.0f);

        sprintf(buffer, "pointLights[%i].linear", pointLightCount);
        setUniform(buffer, 0.09f); 

        sprintf(buffer, "pointLights[%i].quadratic", pointLightCount);
        setUniform(buffer, 0.045f); 
        pointLightCount++;
        break;

      case LightType::SPOT:
        break;
    }
  }
  setUniform("pointLightCount", pointLightCount);
}

#endif //SHADER_PROGRAM
