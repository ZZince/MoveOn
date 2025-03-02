#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aColor;

out vec3 ourColor;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
    ourColor = aColor;
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}
