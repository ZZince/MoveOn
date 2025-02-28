#include "Face.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void Face::CalculNormal(const std::vector<Vertice>& vertices)
{
    if (vertIndices.size() < 3) {
        nx = ny = nz = 0.0f;
        return;
    }

    const Vertice& v0 = vertices[vertIndices[0]];
    const Vertice& v1 = vertices[vertIndices[1]];
    const Vertice& v2 = vertices[vertIndices[2]];

    glm::vec3 vec1(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    glm::vec3 vec2(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);

    glm::vec3 normal = glm::normalize(glm::cross(vec1, vec2));

    nx = normal.x;
    ny = normal.y;
    nz = normal.z;
}
