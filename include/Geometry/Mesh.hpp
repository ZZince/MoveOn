#pragma once

#include <OpenGL/GLM/glm/glm.hpp>

#include <vector>

#include "Geometry/Vertice.hpp"
#include "Geometry/Face.hpp"
#include "Graphics/Shader.hpp"

class Mesh
{
public:
    std::vector<Vertice> m_vertices;
    std::vector<Face> m_faces;
    Shader *m_shader;

    unsigned int VAO, VBO, EBO;

    Mesh();

    void CreateQuad(std::vector<float> size);
    void CreatePyramid(std::vector<float> size);
    void CreateSphere(std::vector<float> size);

    void SetupMesh();
    void ComputeNormals();
    void Render() const;

    void SetShader(Shader *shader) { m_shader = shader; }
};
