#include "Core/Scene.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Shader.hpp"

class Renderer
{
public:
    Renderer();
    void render(const Scene *scene, const Camera *camera) const;

private:
    Shader *m_defaultShader = nullptr;
};