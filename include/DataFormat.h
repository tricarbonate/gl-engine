#ifndef __DATA_FORMATTER_H__
#define __DATA_FORMATTER_H__

#include <iostream>
#include <string>
#include <vector>

#include "DataStructures.h"

/*
 * This namespace contains functions used to convert and format vertices data 
 * into OpenGL usable arrays
 */

namespace DataFormat{

    std::vector<Vertex> getVerticesFromArray(float* arr, unsigned int arraySize);

    std::vector<Vertex> getVerticesFromArrayAndNormals(float* vertices, float* normals, unsigned int arraySize);
}

#endif // __DATA_FORMATTER_H__
