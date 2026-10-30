#include <OpenGL/GLM/glm/glm.hpp>

#include "Core/Component.hpp"

class RotationComponent : public Component
{
public:
    void setRotation(float speed, const glm::vec3 &axis);

private:
    void update(float deltatime) override;
    float m_speed = 0.0f;
    glm::vec3 m_axis = {0.0f, 0.0f, 0.0f};
};