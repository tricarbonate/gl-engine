#ifndef BLOCK_H
#define BLOCK_H

#include "Model.h"

class Block : public Model {
  public:
    Block() = default; 
    Block(Mesh* mesh, ShaderProgram* shaderProgram, glm::vec3 position);

  private:
    
};


#endif // BLOCK_H
