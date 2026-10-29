#pragma once
#include <vector>
#include <memory>
#include "MoveOnObject.hpp"

class Scene
{
public:
    Scene();
    void addObject(std::unique_ptr<MoveOnObject> object);
    void update(float deltatime);
    const std::vector<std::unique_ptr<MoveOnObject>> &getObjects() const;

private:
    std::vector<std::unique_ptr<MoveOnObject>> m_objects;
};
