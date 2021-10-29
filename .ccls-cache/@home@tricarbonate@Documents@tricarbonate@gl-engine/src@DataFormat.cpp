#include "../include/DataFormat.h"

namespace DataFormat{ 

    std::vector<Vertex> getVerticesFromArray(float* arr,
            unsigned int nVertices){
      std::vector<Vertex> v = std::vector<Vertex>();
      for(unsigned int i = 0; i < nVertices * 8; i += 8){
        Vertex vertex;
        vertex.position = glm::vec3(arr[i], arr[i + 1], arr[i + 2]);
        vertex.normal = glm::vec3(arr[i + 3], arr[i + 4], arr[i + 5]);
        vertex.texCoords = glm::vec2(arr[i + 6], arr[i + 7]);
        v.push_back(vertex);
      }
      return v;
    }

    std::vector<Vertex> getVerticesFromArrayAndNormals(float* vertices,
            float* normals, unsigned int nVertices){
      std::vector<Vertex> v = std::vector<Vertex>();
      for(unsigned int i = 0; i < nVertices * 3; i+=3){
        Vertex vertex;
        vertex.position = glm::vec3(vertices[i], vertices[i+1], vertices[i+2]);
        vertex.normal = glm::vec3(normals[i], normals[i+1], normals[i+2]);
        vertex.texCoords = glm::vec2(0.0f, 0.0f);
        v.push_back(vertex);
      }
      return v;
    }
}
