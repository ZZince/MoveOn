#include "RendableComponent.hpp"

void RendableComponent::setVisibility(bool visibility)
{
    m_visible = visibility;
}

void RendableComponent::switchVisibility()
{
    m_visible = !m_visible;
}

bool RendableComponent::getVisibility() const
{
    return m_visible;
}

void RendableComponent::setMesh(std::shared_ptr<Mesh> mesh)
{
    m_mesh = std::move(mesh);
}

Mesh *RendableComponent::getMesh() const
{
    return m_mesh.get();
}

void RendableComponent::setColor(glm::vec3 color)
{
    m_color = color;
}

glm::vec3 RendableComponent::getColor() const
{
    return m_color;
}

void RendableComponent::update(float deltatime) {}