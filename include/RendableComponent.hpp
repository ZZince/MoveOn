#pragma once
#include "Component.hpp"
#include "Mesh.hpp"
#include "OpenGL/GLM/glm/glm.hpp"
#include <memory>
class RendableComponent : public Component
{
public:
    void setVisibility(bool visibility);
    void setMesh(std::shared_ptr<Mesh> mesh);
    void switchVisibility();
    bool getVisibility() const;
    glm::vec3 getColor() const;
    void setColor(glm::vec3 color);
    Mesh *getMesh() const;
    void update(float deltatime);

private:
    bool m_visible = true;
    std::shared_ptr<Mesh> m_mesh = nullptr;
    glm::vec3 m_color = {0.0f, 0.0f, 0.0f};
};