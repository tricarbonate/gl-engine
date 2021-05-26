#ifndef __AABB_H__
#define __AABB_H__

#include "BoundingShape.h"

#include <vector>
#include <iostream>

#include "glm/vec3.hpp"

class AABB : public virtual BoundingShape {

  public: 
    AABB();
    AABB(glm::vec3 min, glm::vec3 max);
    ~AABB();

    void createMesh();

    void constructFromVertices(const std::vector<Vertex>& vertices);

    void draw();

    glm::vec3 getMax() { return max_; }
    glm::vec3 getMin() { return min_; }

  private:
    glm::vec3 min_;
    glm::vec3 max_;
};

#endif // __AABB_H__
