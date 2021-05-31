#ifndef __CHUNK_H__
#define __CHUNK_H__

#include <GL/glew.h>

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "Perlin.h"

//noise params
const int octaves = 5;
const float meshHeight = 16;  // Vertical scaling
const float noiseScale = 64;  // Horizontal scaling
const float persistence = 0.5;
const float lacunarity = 2;

const int chunkWidth = 127;
const int chunkHeight = 127;

const float WATER_HEIGHT = 0.1f;

class Chunk {
public:

    Chunk();
    ~Chunk();

    // creates the VAO with chunk data
    void generateMapChunk(int xOffset, int zOffset);

    GLuint getVao() { return vao_; }

private:
    // methods for chunk data generation
    std::vector<GLuint> generateIndices();
    std::vector<float> generateNoiseMap(int xOffset, int zOffset);
    std::vector<float> generateVertices(const std::vector<float> &noiseMap);
    std::vector<float> generateNormals(const std::vector<GLuint> &indices, const std::vector<float> &vertices);
    std::vector<float> generateColor(const std::vector<float> &vertices, int xOffset, int zOffset);

    std::vector<GLuint> indices_;
    std::vector<float> noiseMap_;
    std::vector<float> vertices_;
    std::vector<float> normals_;
    std::vector<float> colors_;

    GLuint vao_, ebo_, vbo_[3];
};

#endif // __CHUNK_H__
