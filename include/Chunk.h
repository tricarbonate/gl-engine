#ifndef __CHUNK_H__
#define __CHUNK_H__

#include <GL/glew.h>

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "Perlin.h"


//noise params
const int OCTAVES = 5;
const float MESH_HEIGHT = 0;  // Vertical scaling
const float NOISE_SCALE = 64;  // Horizontal scaling
const float PERSISTENCE = 0.5;
const float LACUNARITY = 2;

const int CHUNK_WIDTH = 127;
const int CHUNK_HEIGHT = 127;

const float WATER_HEIGHT = 0.1f;

class Chunk {
public:

    Chunk();
    ~Chunk();

    // creates the VAO with chunk data
    void generateMapChunk(int xOffset, int zOffset);

    GLuint getVao() { return vao_; }

    double getHeight(const int x, const int z);

private:
    // methods for chunk data generation
    std::vector<GLuint> generateIndices();
    std::vector<float> generateNoiseMap(int xOffset, int zOffset);
    std::vector<float> generateVertices(const std::vector<float> &noiseMap);
    std::vector<float> generateNormals(const std::vector<GLuint> &indices, const std::vector<float> &vertices);
    std::vector<float> generateColor(const std::vector<float> &vertices);

    std::vector<GLuint> indices_;
    std::vector<float> noiseMap_;
    std::vector<float> vertices_;
    std::vector<float> normals_;
    std::vector<float> colors_;


    GLuint vao_, ebo_, vbo_[3];
};

#endif // __CHUNK_H__
