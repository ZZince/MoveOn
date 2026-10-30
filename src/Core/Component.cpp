#include "Core/Component.hpp"
#include "Core/MoveOnObject.hpp"

void Component::update(float deltatime)
{
    return;
}

void Component::setOwner(MoveOnObject *object)
{
    m_object = object;
}

MoveOnObject *Component::getOwner() const
{
    return m_object;
}