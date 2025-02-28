#ifndef VERTICE_H
#define VERTICE_H

class Vertice
{
public:
    float x, y, z;       
    float r, g, b;       
    float nx, ny, nz;


    Vertice(float px = 0.0f, float py = 0.0f, float pz = 0.0f,
        float red = 1.0f, float green = 1.0f, float blue = 1.0f)
        : x(px), y(py), z(pz), r(red), g(green), b(blue) {
    }
};

#endif
