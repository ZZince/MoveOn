#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Mesh.hpp"
#include "Light.hpp"
#include "Camera.hpp"

class Scene
{
public:
    std::vector<Mesh*>   m_meshes;
    std::vector<Light*>  m_lights;
    std::vector<Camera*> m_cameras;

    Scene();
    void AddMesh(Mesh* mesh);
    void AddLight(Light* light);
    void AddCamera(Camera* camera);

    void Render();
};

#endif
