#include "Transform.hpp"
#include <OpenGL/GLM/glm/gtc/matrix_transform.hpp>

Transform::Transform(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation)
    : m_position(position),
      m_scale(scale),
      m_rotation(glm::quat(glm::radians(rotation)))
{
}

glm::vec3 Transform::getPosition() const
{
    return m_position;
}

glm::vec3 Transform::getScale() const
{
    return m_scale;
}

glm::quat Transform::getRotate() const
{
    return m_rotation;
}

void Transform::setPosition(const glm::vec3 &position)
{
    m_position = position;
}

void Transform::setScale(const glm::vec3 &scale)
{
    m_scale = scale;
}

void Transform::setRotation(const glm::quat &rotation)
{
    m_rotation = rotation;
}

void Transform::translate(const glm::vec3 &offset)
{
    m_position += offset;
}

void Transform::resetScale()
{
    m_scale = glm::vec3(1.0f);
}

void Transform::scale(const glm::vec3 &factor)
{
    m_scale *= factor;
}

void Transform::scale(const float factor)
{
    m_scale *= factor;
}

void Transform::resetRotation()
{
    m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

void Transform::rotate(float angle, const glm::vec3 &axis)
{
    if (glm::length(axis) < 0.00001f)
        return;

    glm::quat q = glm::angleAxis(
        glm::radians(angle),
        glm::normalize(axis));

    m_rotation = glm::normalize(m_rotation * q);
}

void Transform::rotate(const glm::quat &quaternion_angle_axis)
{
    m_rotation = glm::normalize(quaternion_angle_axis);
}

glm::mat4 Transform::getLocalMatrix() const
{
    glm::mat4 T = glm::translate(glm::mat4(1.0f), m_position);

    glm::mat4 R = glm::mat4_cast(m_rotation);

    glm::mat4 S = glm::scale(glm::mat4(1.0f), m_scale);

    return T * R * S;
}