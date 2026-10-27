#pragma once
#include "Component.hpp"
class RendableComponent : Component
{
public:
    void setVisibility(bool visibility);
    void switchVisibility();
    bool getVisibility();
    void update(float deltatime);

private:
    bool m_visible = true;
};