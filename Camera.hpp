#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    float x, y, z;       
    float pitch, yaw;   

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    Camera(float startX = 0.0f, float startY = 0.0f, float startZ = 5.0f);

    void UpdateViewMatrix();
    void UpdateProjectionMatrix(float fovDegrees, float aspectRatio, float nearPlane, float farPlane);
    glm::mat4 GetViewProjectionMatrix() const;

private:
    void UpdateCameraVectors(glm::vec3& front, glm::vec3& up);
};

#endif
