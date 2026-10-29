#pragma once

#include <OpenGL/GLM/glm/glm.hpp>
#include <OpenGL/GLM/glm/gtc/quaternion.hpp>

#include <vector>
#include <memory>

class Transform
{
public:
    void setPosition(const glm::vec3 &position);
    void setScale(const glm::vec3 &scale);
    void setRotation(const glm::quat &rotation);
    void rotate(const glm::quat &quaternion_angle_axis);
    void rotate(const float angle, const glm::vec3 &axis);
    void resetRotation();
    void translate(const glm::vec3 &offset);
    void scale(const float factor);
    void scale(const glm::vec3 &factor);
    void resetScale();
    Transform(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation);
    Transform();
    glm::vec3 getPosition() const;
    glm::vec3 getScale() const;
    glm::quat getRotate() const;
    glm::mat4 getLocalMatrix() const;

private:
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::quat m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
};