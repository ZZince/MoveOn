#include "Scene.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
class Renderer
{
public:
    Renderer();
    void render(const Scene *scene, const Camera *camera) const;

private:
    Shader *m_defaultShader = nullptr;
};