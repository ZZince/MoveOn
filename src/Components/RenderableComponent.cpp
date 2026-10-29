#include "Components/RenderableComponent.hpp"

void RenderableComponent::setVisibility(bool visibility)
{
    m_visible = visibility;
}

void RenderableComponent::switchVisibility()
{
    m_visible = !m_visible;
}

bool RenderableComponent::getVisibility() const
{
    return m_visible;
}

void RenderableComponent::setMesh(std::shared_ptr<Mesh> mesh)
{
    m_mesh = std::move(mesh);
}

Mesh *RenderableComponent::getMesh() const
{
    return m_mesh.get();
}

void RenderableComponent::setColor(glm::vec3 color)
{
    m_color = color;
}

glm::vec3 RenderableComponent::getColor() const
{
    return m_color;
}

void RenderableComponent::update(float deltatime) {}