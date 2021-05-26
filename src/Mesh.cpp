#include "../include/Mesh.h"

Mesh::Mesh()
{}

Mesh::Mesh(std::vector<Vertex> vertices, Material material,
        std::vector<GLuint> indices):
  vertices_(vertices),
  indices_(indices),
  material_(material)
{
  createMesh();
}

Mesh::~Mesh(){}

void Mesh::createMesh(){
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &verticesVbo_);
  glGenBuffers(1, &indicesVbo_);

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, verticesVbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), &vertices_[0], GL_STATIC_DRAW);  

  if(indices_.size() != 0){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVbo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint), 
                 &indices_[0], GL_STATIC_DRAW);
  }


  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);


  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
  // vertex texture coords
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

  glBindVertexArray(0);
}

// with old method:
void Mesh::createMesh(GLfloat *vertices, GLuint *indices, uint nV, uint nI){
  indexCount_ = nI;
  vertexCount_ = 36 * 2;
  
  glGenVertexArrays(1, &vao_); // generation of VAO
  glBindVertexArray(vao_);

  glGenBuffers(1, &indicesVbo_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVbo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
      sizeof(indices[0]) * nI, indices, GL_STATIC_DRAW);

  glGenBuffers(1, &verticesVbo_); // generation of VBO
  glBindBuffer(GL_ARRAY_BUFFER, verticesVbo_);
  glBufferData(GL_ARRAY_BUFFER, 
      sizeof(vertices[0]) * nV, vertices, GL_STATIC_DRAW); // passing vertices data to VBO

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
      sizeof(vertices[0]) * 6, (void*)(0));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
      sizeof(vertices[0]) * 6, (void*)(sizeof(vertices[0]) * 3));
  glEnableVertexAttribArray(1);

  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Mesh::createInstanced(std::vector<glm::vec3> offsets){
  glGenBuffers(1, &instanceVbo_);
  glBindBuffer(GL_ARRAY_BUFFER, instanceVbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(offsets), &offsets_[0],
      GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);


  glEnableVertexAttribArray(3);
  glBindBuffer(GL_ARRAY_BUFFER, instanceVbo_);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glVertexAttribDivisor(3, 1);

  offsets_ = offsets;
}

void Mesh::renderMesh(ShaderProgram& shader, bool indices){
  /* glActiveTexture(GL_TEXTURE0); */
  /* shader.setUniform("material.diffuse", (unsigned int)0); */
  /* material_.diffuse->bind(); */

  /* glActiveTexture(GL_TEXTURE0 + 1); */
  /* shader.setUniform("material.specular", (unsigned int)1); */
  /* material_.specular->bind(); */

  /* shader.setUniform("material.shininess", material_.shininess); */
  
  /* glActiveTexture(GL_TEXTURE0); */

  glBindVertexArray(vao_);
  if(indices_.size() != 0){
    if(offsets_.size() > 0){
      glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)indices_.size(), GL_UNSIGNED_INT, 0,
          offsets_.size());
    }
    else{
      glDrawElements(GL_TRIANGLES, (GLsizei)indices_.size(), GL_UNSIGNED_INT, 0);
    }
  }
  else{
    if(offsets_.size() > 0){
      glDrawArraysInstanced(GL_TRIANGLES, 0, (GLsizei)vertices_.size(), 
         10); 
    }
    else{
      glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices_.size());
    }
  }
  glBindVertexArray(0);
}

void Mesh::renderMesh(){
  glBindVertexArray(vao_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVbo_);
  glDrawElements(GL_TRIANGLES, indexCount_, GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}


