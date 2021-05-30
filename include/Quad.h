#ifndef __QUAD_H__
#define __QUAD_H__

#include "Model.h"

class Quad : public Model {
  public:

    Quad() = default;
    Quad(std::string mesh, ShaderProgram* shaderProrgam, glm::vec3 position);

  private:
     
};

#endif //__QUAD_H__
