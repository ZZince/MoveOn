#pragma once

class Component
{
public:
    virtual void update(float deltatime);
    virtual ~Component() = default;
};