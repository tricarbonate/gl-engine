#ifndef __MIRROR_H__
#define __MIRROR_H__

#include "Model.h"

/* A mirror is seen as a rectangular Model
 */

class Mirror : public Model{
  public:
    Mirror();
    Mirror(std::string mesh, ShaderProgram* shaderProgram, glm::vec3 position);
    ~Mirror();


  private:
    void drawReflection();
};

#endif // __MIRROR_H__
