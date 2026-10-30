#include <algorithm>

#include "Core/MoveOnObject.hpp"

MoveOnObject::MoveOnObject()
{
    m_transform = Transform();
}

MoveOnObject::MoveOnObject(const Transform transform, std::shared_ptr<Mesh> mesh)
{
    m_transform = transform;
}

MoveOnObject::MoveOnObject(const Transform &transform, std::shared_ptr<Mesh> mesh, std::vector<std::unique_ptr<Component>> components)
{
    m_transform = transform;
    m_components = std::move(components);
}

MoveOnObject::MoveOnObject(Transform transform, std::vector<std::unique_ptr<Component>> components)
{
    m_transform = transform;
    m_components = std::move(components);
}

void MoveOnObject::setTransform(Transform transform)
{
    m_transform = transform;
}

void MoveOnObject::setParent(MoveOnObject *parent)
{
    if (parent == nullptr)
    {
        m_parent = nullptr;
        return;
    }

    for (MoveOnObject *current = parent;
         current != nullptr;
         current = current->getParent())
    {
        if (current == this)
        {
            return;
        }
    }

    m_parent = parent;
}

void MoveOnObject::addComponent(std::unique_ptr<Component> component)
{
    if (!component)
    {
        return;
    }
    component->setOwner(this);
    m_components.push_back(std::move(component));
}

void MoveOnObject::update(float deltaTime)
{
    for (auto &component : m_components)
    {
        component->update(deltaTime);
    }
}

const Transform &MoveOnObject::getTransform() const
{
    return m_transform;
}

Transform &MoveOnObject::getTransform()
{
    return m_transform;
}

MoveOnObject *MoveOnObject::getParent() const
{
    return m_parent;
}

glm::mat4 MoveOnObject::getWorldMatrix() const
{
    glm::mat4 localMatrix = m_transform.getLocalMatrix();

    if (m_parent == nullptr)
    {
        return localMatrix;
    }

    return m_parent->getWorldMatrix() * localMatrix;
}