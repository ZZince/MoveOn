#include "Renderer.hpp"
#include "RendableComponent.hpp"
#include "Mesh.hpp"
#include <OpenGL/GLM/glm/glm.hpp>

Renderer::Renderer() = default;
void Renderer::render(const Scene *scene, const Camera *camera) const
{
    if (!scene || !camera)
    {
        return;
    }
    const RendableComponent *rendableComponent;
    const Mesh *mesh;
    const Shader *shader;

    glm::mat4 viewProjectionMatrix = camera->GetViewProjectionMatrix();
    glm::mat4 worldMatrix;
    for (auto &object : scene->getObjects())
    {
        rendableComponent = object->findComponent<RendableComponent>();
        if (!rendableComponent)
        {
            continue;
        }

        if (!rendableComponent->getVisibility())
        {
            continue;
        }
        mesh = rendableComponent->getMesh();
        if (!mesh)
        {
            continue;
        }
        worldMatrix = object->getWorldMatrix();
        shader = mesh->m_shader;
        if (!shader)
        {
            shader = m_defaultShader;
        }
        glm::vec3 color = rendableComponent->getColor();

        shader->Use();

        shader->setUniformMat4("uModel", worldMatrix);
        shader->setUniformMat4("uViewProjection", viewProjectionMatrix);
        shader->setUniform3f("uColor", color.r, color.g, color.b);
        mesh->Render();
    }
}