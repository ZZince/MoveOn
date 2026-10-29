#include "Scene.hpp"

void Scene::addObject(std::unique_ptr<MoveOnObject> object)
{
    m_objects.push_back(std::move(object));
}

void Scene::update(float deltatime)
{
    for (auto &m_object : m_objects)
    {
        m_object->update(deltatime);
    }
}

const std::vector<std::unique_ptr<MoveOnObject>> &Scene::getObjects() const
{
    return m_objects;
}

Scene::Scene() = default;
/*
void Scene::Render()
{
    if (m_cameras.empty())
        return;

    Camera* cam = m_cameras[0];

    for (auto& mesh : m_meshes)
    {
        if (mesh->m_shader)
        {
            mesh->m_shader->Use();

            mesh->m_shader->setUniformMat4("uProjection", cam->projectionMatrix);
            mesh->m_shader->setUniformMat4("uView", cam->viewMatrix);

            glm::mat4 model = glm::mat4(1.0f);
            mesh->m_shader->setUniformMat4("uModel", model);

            glm::vec3 cameraPos(cam->x, cam->y, cam->z);
            mesh->m_shader->setUniform3f("uViewPos", cameraPos.x, cameraPos.y, cameraPos.z);

            int nbLights = static_cast<int>(m_lights.size());
            mesh->m_shader->setUniform("numLights", nbLights);

            for (int i = 0; i < nbLights; ++i)
            {
                Light* light = m_lights[i];

                std::string posName = "lights[" + std::to_string(i) + "].pos";
                std::string colorName = "lights[" + std::to_string(i) + "].color";

                mesh->m_shader->setUniform3f(posName, light->x, light->y, light->z);
                mesh->m_shader->setUniform3f(colorName, light->r, light->g, light->b);
            }

            mesh->m_shader->setUniform3f("objectColor", mesh->m_vertices[0].r, mesh->m_vertices[0].g, mesh->m_vertices[0].b);
            mesh->m_shader->setUniform("edgeThreshold", 0.2f);
            mesh->m_shader->setUniform("ambientStrength", 0.2f);
            mesh->m_shader->setUniform("specularStrength", 0.5f);
            mesh->m_shader->setUniform("shininess", 32.0f);

            mesh->Render();
        }
    }
}
*/
