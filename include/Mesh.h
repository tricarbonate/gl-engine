#ifndef MESH_H
#define MESH_H

#include "Texture.h"
#include "ShaderProgram.h"

#include <iostream>

#include <GLFW/glfw3.h>

struct Vertex{
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoords;
};

//Material contains textures for diffuse maps
// specular maps, normal maps, height maps
// and a shininess factor
struct Material{
  Texture* diffuse;
  Texture* specular;
  Texture* normal;
  Texture* height;
  float shininess;
};

class Mesh 
{
  public:
    Mesh();
    Mesh(std::vector<Vertex> vertices, Material material,
        std::vector<GLuint> indices);
    ~Mesh();

    // nV and nI are number of vertices and indices
    void createMesh(GLfloat *vertices, GLuint *indices, uint nV, uint nI);

    void createMesh();
    void createInstanced(std::vector<glm::vec3> offsets);

    void renderMesh();
    void renderMesh(ShaderProgram& shader, bool indices);

    Material& getMaterial() { return material_; }

    const std::vector<Vertex>& getVertices() const {return vertices_;}
    GLuint getVAO() const { return vao_; }

  protected:

    // Mesh data
    Material material_;
    std::vector<glm::vec3> offsets_;

    GLuint indexCount_, vertexCount_;
    GLuint vao_, indicesVbo_, verticesVbo_, instanceVbo_;

    std::vector<Vertex> vertices_;
    std::vector<GLuint> indices_;
};

#endif // MESH
