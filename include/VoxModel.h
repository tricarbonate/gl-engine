#ifndef __VOXMODEL_H__
#define __VOXMODEL_H__

#include "Model.h"
#include "Voxel.h"

// A Vox model is a model built from Voxel meshes
// positions_ declares the positions of all the Voxels
class VoxModel : public Model
{
  public:
    VoxModel();
    VoxModel(glm::vec3 position, const char* shaderName, ShaderProgram* shaderProgram);
    ~VoxModel();

    void addVoxel(glm::vec3 at);

    const std::vector<glm::vec3>& getPositions() { return positions_; }

  private:
    std::vector<glm::vec3> positions_;
};

#endif // __VOXMODEL_H__
