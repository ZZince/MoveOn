#include "RendableComponent.hpp"

void RendableComponent::setVisibility(bool visibility)
{
    m_visible = visibility;
}

void RendableComponent::switchVisibility()
{
    m_visible != m_visible;
}

bool RendableComponent::getVisibility()
{
    return m_visible;
}

void RendableComponent::update(float deltatime) {}