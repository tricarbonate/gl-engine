#ifndef BLOCK_H
#define BLOCK_H

#include "Model.h"

/* Basic cube-shaped model
//
// */
class Block : public Model {
  public:
    Block() = default; 
    Block(std::string mesh, ShaderProgram* shaderProgram, glm::vec3 position);

  private:
    
    double length_;
};


#endif // BLOCK_H
