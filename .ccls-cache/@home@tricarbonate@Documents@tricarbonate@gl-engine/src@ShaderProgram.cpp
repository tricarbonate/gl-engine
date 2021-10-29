#include "../include/ShaderProgram.h"

ShaderProgram::ShaderProgram(std::vector<std::pair<const char*, GLenum> > locations)
{
  for(size_t i = 0; i < locations.size(); i++){
    locs_.push_back(std::pair<const char*, GLenum>(locations[i].first, locations[i].second));
  }
}


ShaderProgram::ShaderProgram(){} // default constructor 

ShaderProgram::~ShaderProgram(){}

std::string ShaderProgram::readFile(const char* fileLocation){
  std::string content;
  std::ifstream fileStream(fileLocation, std::ios::in);

  if(!fileStream.is_open()){
    std::cout << "Failed to read " << fileLocation << std::endl; 
  }

  std::string line = "";
  while(!fileStream.eof()){
    std::getline(fileStream, line);
    content.append(line + "\n");
  }

  fileStream.close();
  return content;
}


void ShaderProgram::addShader(GLuint programID, const char* shaderCode, GLenum shaderType){
  GLuint shader = glCreateShader(shaderType); // create the shader with the entered type

  std::cout << "adding shader: " << shaderType << std::endl;
  const GLchar* code[1];
  code[0] = shaderCode;

  GLint codeLength[1];
  codeLength[0] = (GLint)strlen(shaderCode);

  glShaderSource(shader, 1, code, codeLength); // link the code passed in arguments with the corresponding shader ID.
  glCompileShader(shader);

  // check for errors in shader code and prints result :
  GLint result = 0;
  GLchar eLog[1024] = { 0 };
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  if(!result){
    glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
    std::cout << "Error compiling the shader : " << shaderType << " " << eLog << std::endl;
    return;
  }

  glAttachShader(programID, shader); // once compiled, we want to link the shader with the corresponding program. 
}


void ShaderProgram::addFile(const char* fileLocation, GLenum shaderType){
  locs_.push_back(std::pair<const char*, GLenum>(fileLocation, shaderType));
}

void ShaderProgram::compileProgram(){
  shaderID_ = glCreateProgram();
  if(!shaderID_){
    std::cout << "Error creating the shader program" << std::endl;
    return;
  }

  // add every files bound the this shader program
  for(auto it = locs_.begin(); it != locs_.end(); it++){
    addShader(shaderID_, readFile(it->first).c_str(), it->second);
  }

  GLint result = 0;
  GLchar eLog[1024] = { 0 };
  glLinkProgram(shaderID_);
  glGetProgramiv(shaderID_, GL_LINK_STATUS, &result);
  if(!result){
    glGetProgramInfoLog(shaderID_, sizeof(eLog), NULL, eLog);
    std::cout << "error compiling the program : " << eLog << std::endl;
    return;
  }
}

void ShaderProgram::useProgram(){
  glUseProgram(shaderID_);
}
