#include "Mesh.hpp"
#include <glew.h>
#include <iostream>
#include <cmath>
#define M_PI 3.14159265358979323846

Mesh::Mesh()
    : m_shader(nullptr), VAO(0), VBO(0), EBO(0)
{
}

void Mesh::SetupMesh()
{
    std::vector<float> vertexData;
    vertexData.reserve(m_vertices.size() * 9);

    for (const auto& v : m_vertices) {
        // Position
        vertexData.push_back(v.x);
        vertexData.push_back(v.y);
        vertexData.push_back(v.z);
        // Normale
        vertexData.push_back(v.nx);
        vertexData.push_back(v.ny);
        vertexData.push_back(v.nz);
        // Couleur
        vertexData.push_back(v.r);
        vertexData.push_back(v.g);
        vertexData.push_back(v.b);
    }

    std::vector<unsigned int> indices;
    for (const auto& face : m_faces) {

        if (face.vertIndices.size() == 3) {
            indices.push_back(face.vertIndices[0]);
            indices.push_back(face.vertIndices[1]);
            indices.push_back(face.vertIndices[2]);
        }
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        vertexData.size() * sizeof(float),
        vertexData.data(),
        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW);

    GLsizei stride = 9 * sizeof(float);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::ComputeNormals()
{
    for (auto& v : m_vertices) {
        v.nx = 0.0f;
        v.ny = 0.0f;
        v.nz = 0.0f;
    }

    for (auto& face : m_faces) {
        face.CalculNormal(m_vertices);

        for (auto idx : face.vertIndices) {
            m_vertices[idx].nx += face.nx;
            m_vertices[idx].ny += face.ny;
            m_vertices[idx].nz += face.nz;
        }
    }

    for (auto& v : m_vertices) {
        float length = std::sqrt(v.nx * v.nx + v.ny * v.ny + v.nz * v.nz);
        if (length > 0.00001f) {
            v.nx /= length;
            v.ny /= length;
            v.nz /= length;
        }
    }
}

void Mesh::Render()
{
    if (m_shader) {
        m_shader->Use();
    }

    glBindVertexArray(VAO);

    size_t indexCount = m_faces.size() * 3;
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Mesh::Translation(float x, float y, float z)
{
	for (auto& vertice : m_vertices)
	{
		vertice.x += x;
		vertice.y += y;
		vertice.z += z;
	}
}

void Mesh::Change_Color(float r, float g, float b)
{
	for (auto& vertice : m_vertices)
	{
		vertice.r = r;
		vertice.g = g;
		vertice.b = b;
	}
}

void Mesh::CreateQuad(std::vector<float> size)
{
    if (size.size() < 3) {
        std::cerr << "[CreateQuad] Erreur : 'size' doit contenir au moins 3 valeurs (lx, ly, lz)." << std::endl;
        return;
    }

    float lx = size[0];
    float ly = size[1];
    float lz = size[2];

    m_vertices.clear();
    m_faces.clear();

    m_vertices = {
        Vertice(+lx, +ly, +lz), // sommet 0
        Vertice(+lx, +ly, -lz), // sommet 1
        Vertice(+lx, -ly, +lz), // sommet 2
        Vertice(+lx, -ly, -lz), // sommet 3
        Vertice(-lx, +ly, +lz), // sommet 4
        Vertice(-lx, +ly, -lz), // sommet 5
        Vertice(-lx, -ly, +lz), // sommet 6
        Vertice(-lx, -ly, -lz)  // sommet 7
    };


    Face f1({ 0,1,3 });
    Face f2({ 0,3,2 });

    Face f3({ 4,5,7 });
    Face f4({ 4,7,6 });

    Face f5({ 0,1,5 });
    Face f6({ 0,5,4 });

    Face f7({ 2,3,7 });
    Face f8({ 2,7,6 });

    Face f9({ 0,2,6 });
    Face f10({ 0,6,4 });

    Face f11({ 1,3,7 });
    Face f12({ 1,7,5 });

    m_faces.push_back(f1);
    m_faces.push_back(f2);
    m_faces.push_back(f3);
    m_faces.push_back(f4);
    m_faces.push_back(f5);
    m_faces.push_back(f6);
    m_faces.push_back(f7);
    m_faces.push_back(f8);
    m_faces.push_back(f9);
    m_faces.push_back(f10);
    m_faces.push_back(f11);
    m_faces.push_back(f12);

    for (auto& face : m_faces) {
        face.CalculNormal(m_vertices);
    }
}


void Mesh::CreateSphere(std::vector<float> size)
{
    if (size.size() < 3) {
        std::cerr << "[CreateSphere] Erreur : 'size' doit contenir : rayon, nbTheta, nbPhi." << std::endl;
        return;
    }

    float radius = size[0];
    int   nbtheta = static_cast<int>(size[1]); 
    int   nbphi = static_cast<int>(size[2]);  

    m_vertices.clear();
    m_faces.clear();

    //    theta : 0..nbtheta
    //    phi   : 0..nbphi
    //    x = r*cos(thetaRad)*sin(phiRad)
    //    y = r*sin(thetaRad)*sin(phiRad)
    //    z = r*cos(phiRad)
    for (int t = 0; t <= nbtheta; ++t)
    {
        float thetaRad = 2.f * float(M_PI) * float(t) / float(nbtheta);

        for (int p = 0; p <= nbphi; ++p)
        {
            float phiRad = float(M_PI) * float(p) / float(nbphi);

            float x = radius * std::cos(thetaRad) * std::sin(phiRad);
            float y = radius * std::sin(thetaRad) * std::sin(phiRad);
            float z = radius * std::cos(phiRad);

            m_vertices.emplace_back(x, y, z);
        }
    }

    //    Nombre de points par bande : nbphi + 1
    //    iP0 = t*(nbphi+1) + p
    //    iP1 = t*(nbphi+1) + (p+1)
    //    iP2 = (t+1)*(nbphi+1) + (p+1)
    //    iP3 = (t+1)*(nbphi+1) + p
    int rowSize = nbphi + 1;
    for (int t = 0; t < nbtheta; ++t)
    {
        for (int p = 0; p < nbphi; ++p)
        {
            int iP0 = t * rowSize + p;
            int iP1 = t * rowSize + (p + 1);
            int iP2 = (t + 1) * rowSize + (p + 1);
            int iP3 = (t + 1) * rowSize + p;

            // Premier triangle : (iP0, iP1, iP2)
            Face f1({ iP0, iP1, iP2 });
            // Deuxième triangle : (iP0, iP2, iP3)
            Face f2({ iP0, iP2, iP3 });

            m_faces.push_back(f1);
            m_faces.push_back(f2);
        }
    }

    for (auto& face : m_faces) {
        face.CalculNormal(m_vertices);
    }
}

void Mesh::CreatePyramid(std::vector<float> size)
{
    if (size.size() < 3) {
        std::cerr << "[CreatePyramid] Erreur : 'size' doit contenir au moins 3 valeurs (lx, ly, lz)."
            << std::endl;
        return;
    }

    float lx = size[0]; 
    float ly = size[1]; 
    float lz = size[2]; 

    m_vertices.clear();
    m_faces.clear();

    m_vertices.push_back(Vertice(+lx, 0.f, +lz)); 
    m_vertices.push_back(Vertice(+lx, 0.f, -lz)); 
    m_vertices.push_back(Vertice(-lx, 0.f, +lz)); 
    m_vertices.push_back(Vertice(-lx, 0.f, -lz)); 
    m_vertices.push_back(Vertice(0.f, +ly, 0.f)); 

    Face f1({ 0, 1, 4 });
    Face f2({ 1, 3, 4 });
    Face f3({ 3, 2, 4 });
    Face f4({ 2, 0, 4 });

    m_faces.push_back(f1);
    m_faces.push_back(f2);
    m_faces.push_back(f3);
    m_faces.push_back(f4);

    Face f5({ 0, 2, 1 });
    Face f6({ 1, 2, 3 });

    m_faces.push_back(f5);
    m_faces.push_back(f6);

    for (auto& face : m_faces) {
        face.CalculNormal(m_vertices);
    }
}
