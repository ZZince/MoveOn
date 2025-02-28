#ifndef FACE_H
#define FACE_H

#include <vector>
#include "Vertice.hpp"

class Face
{
public:
    std::vector<int> vertIndices;

    float nx, ny, nz;

    Face() : nx(0), ny(0), nz(0) {}
	Face(const std::vector<int>& indices) : vertIndices(indices), nx(0), ny(0), nz(0) {}

    void CalculNormal(const std::vector<Vertice>& vertices);
};

#endif
