#include "Camera.hpp"

Camera::Camera(float startX, float startY, float startZ)
    : x(startX), y(startY), z(startZ),
    pitch(0.0f), yaw(-90.0f)
{
    UpdateViewMatrix();
    UpdateProjectionMatrix(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

void Camera::UpdateViewMatrix()
{
    glm::vec3 front, up;
    UpdateCameraVectors(front, up);

    glm::vec3 cameraPos(x, y, z);
    glm::vec3 lookAt = cameraPos + front;

    viewMatrix = glm::lookAt(cameraPos, lookAt, up);
}

void Camera::UpdateProjectionMatrix(float fovDegrees, float aspectRatio, float nearPlane, float farPlane)
{
    projectionMatrix = glm::perspective(glm::radians(fovDegrees), aspectRatio, nearPlane, farPlane);
}

glm::mat4 Camera::GetViewProjectionMatrix() const
{
    return projectionMatrix * viewMatrix;
}

void Camera::UpdateCameraVectors(glm::vec3& front, glm::vec3& up)
{
    float radPitch = glm::radians(pitch);
    float radYaw = glm::radians(yaw);

    front.x = cos(radYaw) * cos(radPitch);
    front.y = sin(radPitch);
    front.z = sin(radYaw) * cos(radPitch);
    front = glm::normalize(front);

    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);

    glm::vec3 right = glm::normalize(glm::cross(front, worldUp));

    up = glm::normalize(glm::cross(right, front));
}
