#include "../include/Chunk.h"

Chunk::Chunk(){

}


Chunk::~Chunk(){

}

void Chunk::generateMapChunk(int xOffset, int zOffset){
    indices_ = generateIndices();
    noiseMap_ = generateNoiseMap(xOffset, zOffset);
    vertices_ = generateVertices(noiseMap_);
    normals_ = generateNormals(indices_, vertices_);
    colors_ = generateColor(vertices_);

    glGenBuffers(3, vbo_);
    glGenBuffers(1, &ebo_);
    glGenVertexArrays(1, &vao_);

    // Bind vertices to VBO
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), &vertices_[0], GL_STATIC_DRAW);

    // Create element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(int), &indices_[0], GL_STATIC_DRAW);

    // Configure vertex position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Bind vertices to VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
    glBufferData(GL_ARRAY_BUFFER, normals_.size() * sizeof(float), &normals_[0], GL_STATIC_DRAW);

    // Configure vertex normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Bind vertices to VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo_[2]);
    glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(float), &colors_[0], GL_STATIC_DRAW);

    // Configure vertex colors attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
}


std::vector<GLuint> Chunk::generateIndices(){
    std::vector<GLuint> indices;

    for (int y = 0; y < CHUNK_HEIGHT; y++)
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            int pos = x + y*CHUNK_WIDTH;

            if (x == CHUNK_WIDTH - 1 || y == CHUNK_HEIGHT - 1) {
                // Don't create indices for right or top edge
                continue;
            } else {
                // Top left triangle of square
                indices.push_back(pos + CHUNK_WIDTH);
                indices.push_back(pos);
                indices.push_back(pos + CHUNK_WIDTH + 1);
                // Bottom right triangle of square
                indices.push_back(pos + 1);
                indices.push_back(pos + 1 + CHUNK_WIDTH);
                indices.push_back(pos);
            }
        }

    return indices;
}


std::vector<float> Chunk::generateNoiseMap(int xOffset, int zOffset){
    std::vector<float> noiseValues;
    std::vector<float> normalizedNoiseValues;
    std::vector<int> p = get_permutation_vector();

    float amp  = 1;
    float freq = 1;
    float maxPossibleHeight = 0;

    for (int i = 0; i < OCTAVES; i++) {
        maxPossibleHeight += amp;
        amp *= PERSISTENCE;
    }

    for (int y = 0; y < CHUNK_HEIGHT; y++) {
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            amp  = 1;
            freq = 1;
            float noiseHeight = 0;
            for (int i = 0; i < OCTAVES; i++) {
                float xSample = (x + xOffset * (CHUNK_WIDTH-1))  / NOISE_SCALE * freq;
                float ySample = (y + zOffset * (CHUNK_HEIGHT-1)) / NOISE_SCALE * freq;

                float perlinValue = perlin_noise(xSample, ySample, p);
                noiseHeight += perlinValue * amp;

                // Lacunarity  --> Increase in frequency of octaves
                // Persistence --> Decrease in amplitude of octaves
                amp  *= PERSISTENCE;
                freq *= LACUNARITY;
            }

            noiseValues.push_back(noiseHeight);
        }
    }

    for (int y = 0; y < CHUNK_HEIGHT; y++) {
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            // Inverse lerp and scale values to range from 0 to 1
            normalizedNoiseValues.push_back((noiseValues[x + y*CHUNK_WIDTH] + 1) / maxPossibleHeight);
        }
    }

    return normalizedNoiseValues;
}

double Chunk::getHeight(const int x, const int z) {
    float easedNoise = std::pow(noiseMap_[x + z*CHUNK_WIDTH] * 1.1, 3);
    return std::fmax(easedNoise * MESH_HEIGHT, WATER_HEIGHT * 0.5 * MESH_HEIGHT);
}


std::vector<float> Chunk::generateVertices(const std::vector<float> &noiseMap){
    std::vector<float> v;

    for (int y = 0; y < CHUNK_HEIGHT + 1; y++)
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            v.push_back(x);
            // Apply cubic easing to the noise
            float easedNoise = std::pow(noiseMap[x + y*CHUNK_WIDTH] * 1.1, 3);
            // Scale noise to match meshHeight
            // Pervent vertex height from being below WATER_HEIGHT
            v.push_back(std::fmax(easedNoise * MESH_HEIGHT, WATER_HEIGHT * 0.5 * MESH_HEIGHT));
            v.push_back(y);
        }

    return v;
}


std::vector<float> Chunk::generateNormals(const std::vector<GLuint> &indices, const std::vector<float> &vertices){
    int pos;
    glm::vec3 normal;
    std::vector<float> normals;
    std::vector<glm::vec3> verts;

    // Get the vertices of each triangle in mesh
    // For each group of indices
    for (size_t i = 0; i < indices.size(); i += 3) {

        // Get the vertices (point) for each index
        for (size_t j = 0; j < 3; j++) {
            pos = indices[i+j]*3;
            verts.push_back(glm::vec3(vertices[pos], vertices[pos+1], vertices[pos+2]));
        }

        // Get vectors of two edges of triangle
        glm::vec3 U = verts[i+1] - verts[i];
        glm::vec3 V = verts[i+2] - verts[i];

        // Calculate normal
        normal = glm::normalize(-glm::cross(U, V));
        normals.push_back(normal.x);
        normals.push_back(normal.y);
        normals.push_back(normal.z);
    }

    return normals;
}

std::vector<float> Chunk::generateColor(const std::vector<float> &vertices){
    std::vector<float> colors;
    glm::vec3 color = glm::vec3(0.1f, 8.0f, 0.1f);
    for(size_t i = 1; i < vertices.size(); i+=3){
        color = glm::vec3(0.5 + vertices[i] / 2, 0.8 + cos(vertices[i]) / 10, vertices[i] / 2);
        color /= 10.0;
        //colors.push_back(color.r);
        //colors.push_back(color.g);
        //colors.push_back(color.b);

        colors.push_back(0.0f);
        colors.push_back(0.0f);
        colors.push_back(0.0f);
    }

    return colors;
}
