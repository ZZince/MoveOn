#ifndef LIGHT_H
#define LIGHT_H

class Light
{
public:
    float x, y, z;      
    float r, g, b;      

    Light(float posX = 0.0f, float posY = 10.0f, float posZ = 0.0f,
        float red = 1.0f, float green = 1.0f, float blue = 1.0f);
};

#endif
