#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <vector>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Chunk.h"
#include "ShaderProgram.h"
#include "State.h"

const int zMapChunk = 3;
const int xMapChunk = 3;

class Terrain {
  public:

    Terrain();
    ~Terrain();

    //void generateChunk(GLuint& vao, int xOffset, int zOffset);
    //
    void draw(glm::mat4 &model, glm::mat4 &view, glm::mat4 &proj, ShaderProgram &shaderProgram);

    const std::vector<Chunk>& getChunks() { return chunks_; }

    //getters
    double getBaseHeight() { return baseHeight_; }
    double getHeight(const double x, const double z);


    // TODO for btHeightfield
    int getWidth();
    int getLength();
    const void* getRawData();
    float getHeightScale();
    float getMinHeight();
    float getMaxHeight();

  private:
    std::vector<Chunk> chunks_;

    Chunk getChunk(const double x, const double z);
    double baseHeight_;
};

#endif // __TERRAIN_H__
