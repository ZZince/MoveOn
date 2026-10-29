#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 ourColor;

uniform mat4 uViewProjection;
uniform mat4 uModel;
uniform vec3 uColor;

void main()
{
    ourColor = uColor;
    gl_Position = uViewProjection * uModel * vec4(aPos, 1.0);
}
