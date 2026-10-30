#include "Components/RotationComponent.hpp"
#include "Core/MoveOnObject.hpp"

void RotationComponent::setRotation(float speed, const glm::vec3 &axis)
{
    m_speed = speed;
    m_axis = axis;
}

void RotationComponent::update(float deltatime)
{
    getOwner()->getTransform().rotate(m_speed * deltatime, m_axis);
}