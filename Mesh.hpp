#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include "Vertice.hpp"
#include "Face.hpp"
#include "Shader.hpp"

class Mesh
{
public:
    std::vector<Vertice> m_vertices;
    std::vector<Face>    m_faces;
    Shader* m_shader;

    unsigned int VAO, VBO, EBO;

    Mesh();

    void CreateQuad(std::vector<float> size);
    void CreatePyramid(std::vector<float> size);
    void CreateSphere(std::vector<float> size);

    void SetupMesh();
    void ComputeNormals();  
    void Render();
	void Change_Color(float r, float g, float b);
	void Translation(float x, float y, float z);

    void SetShader(Shader* shader) { m_shader = shader; }
};

#endif
