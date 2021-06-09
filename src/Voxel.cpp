#include "../include/Voxel.h"


Voxel::Voxel():
    Mesh(DataFormat::getVerticesFromArray(voxelCoords, 36),
            Assets::materials.at("container"), std::vector<GLuint>())
{}

Voxel::~Voxel(){}
