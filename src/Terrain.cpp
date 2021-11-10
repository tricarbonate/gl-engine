#include "../include/Terrain.h"

Terrain::Terrain() :
    baseHeight_(-10.0f)
{
    chunks_.resize(xMapChunk * zMapChunk);
    for(int x = 0; x < xMapChunk; x++){
        for(int z = 0; z < zMapChunk; z++){
            chunks_[x + z*xMapChunk].generateMapChunk(x, z);
        }
    }
}

Terrain::~Terrain()
{
}

void Terrain::draw(glm::mat4 &model, glm::mat4& view, glm::mat4 &proj, ShaderProgram &shaderProgram){

    shaderProgram.setUniform("isFlat", (unsigned int)State::terrainFlatShading_);

    glActiveTexture(GL_TEXTURE0);
    shaderProgram.setUniform("material.diffuse", (unsigned int)0);
    glActiveTexture(GL_TEXTURE0 + 1);
    shaderProgram.setUniform("material.specular", (unsigned int)1);
    shaderProgram.setUniform("material.shininess", (unsigned int)1);
    glActiveTexture(GL_TEXTURE0);

    for(int z = 0; z < zMapChunk; z++){
        for(int x = 0; x < xMapChunk; x++){

           model = glm::mat4(1.0f); 
           model = glm::translate(model, glm::vec3(-chunkWidth / 2.0 + (chunkWidth - 1) * x,
                       baseHeight_,
                       -chunkHeight / 2.0 + (chunkHeight - 1) * z));

           glm::mat4 mvp = proj * view * model;
           shaderProgram.setUniform("mvp", mvp);
           shaderProgram.setUniform("model", model);


           glBindVertexArray(chunks_[x + z*xMapChunk].getVao());
           glDrawElements(GL_TRIANGLES, chunkWidth * chunkHeight * 6, GL_UNSIGNED_INT, 0);
        }
    }
}

double Terrain::getHeight(const double x, const double z) {
    Chunk chunk = getChunk(x, z);
    //chunk.getHeight();
    return chunk.getHeight((int)x % chunkWidth, (int)z % chunkWidth);
}

Chunk Terrain::getChunk(const double x, const double z) {
    const int X = ceil(x / chunkWidth);
    const int Z = ceil(z / chunkWidth);
    //std::cout << X << " " << Z << std::endl;
    return chunks_[X + Z * xMapChunk];
}

int Terrain::getWidth(){
    return 0;
}
int Terrain::getLength(){
    return 0;
}
const void* Terrain::getRawData(){
    return 0;
}
float Terrain::getHeightScale(){
    return 0.0f;
}
float Terrain::getMinHeight(){
    return 0.0f;
}
float Terrain::getMaxHeight(){
    return 0.0f;
}

