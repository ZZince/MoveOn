#pragma once

class MoveOnObject;

class Component
{
public:
    virtual void update(float deltatime);
    virtual ~Component() = default;
    void setOwner(MoveOnObject *object);
    MoveOnObject *getOwner() const;

private:
    MoveOnObject *m_object = nullptr;
};