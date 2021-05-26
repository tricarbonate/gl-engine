#include "../include/AABB.h"


AABB::AABB():
    min_(glm::vec3(0.0f, 0.0f, 0.0f)),
    max_(glm::vec3(0.0f, 0.0f, 0.0f))
{}

AABB::AABB(glm::vec3 min, glm::vec3 max):
    min_(min),
    max_(max)
{

}

AABB::~AABB(){}


void AABB::constructFromVertices(const std::vector<Vertex>& vertices){
    min_ = glm::vec3(vertices[0].position.r, vertices[0].position.g, vertices[0].position.b);
    max_ = glm::vec3(vertices[0].position.r, vertices[0].position.g, vertices[0].position.b);

    for(size_t i = 1; i < vertices.size(); i++){
        min_.r = fmin(min_.r, vertices[i].position.r);                
        min_.g = fmin(min_.g, vertices[i].position.g);                
        min_.b = fmin(min_.b, vertices[i].position.b);                

        max_.r = fmax(max_.r, vertices[i].position.r);
        max_.g = fmax(max_.g, vertices[i].position.g);
        max_.b = fmax(max_.b, vertices[i].position.b);
    }


    // once the min and max are found
    // we can define the vertices to be able to draw the bound volume
    this->vertices_.push_back(Vertex{
            glm::vec3(min_.r, min_.g, min_.b),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec2(0.0f, 0.0f)
    });
    this->vertices_.push_back(Vertex{
            glm::vec3(max_.r, min_.g, min_.b),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec2(0.0f, 0.0f)
    });
    this->vertices_.push_back(Vertex{
            glm::vec3(min_.r, max_.g, min_.b),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec2(0.0f, 0.0f)
    });
    this->vertices_.push_back(Vertex{
            glm::vec3(max_.r, max_.g, min_.b),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec2(0.0f, 0.0f)
    });
    
    // back face
    this->vertices_.push_back(Vertex{
            glm::vec3(min_.r, min_.g, max_.b),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec2(0.0f, 0.0f)
    });
    this->vertices_.push_back(Vertex{
            glm::vec3(max_.r, min_.g, max_.b),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec2(0.0f, 0.0f)
    });
    this->vertices_.push_back(Vertex{
            glm::vec3(min_.r, max_.g, max_.b),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec2(0.0f, 0.0f)
    });
    this->vertices_.push_back(Vertex{
            glm::vec3(max_.r, max_.g, max_.b),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec2(0.0f, 0.0f)
    });

    
    this->indices_ = std::vector<GLuint>({
        0, 1, 2,
        1, 2, 3,

        4, 5, 6,
        5, 6, 7,

        4, 5, 0,
        5, 0, 1,

        0, 2, 4,
        2, 4, 6,

        1, 3, 7,
        1, 7, 5,

        2, 3, 6,
        3, 6, 7
    });

    this->Mesh::createMesh();
}



void AABB::draw(){
  glBindVertexArray(vao_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVbo_);
  glDrawElements(GL_LINES, (GLsizei)indices_.size(), GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
