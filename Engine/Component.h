#pragma once

namespace GameEngine
{
    class GameObject;

    class Component
    {
    public:
        Component(GameObject* gameObject);
        virtual ~Component();

        virtual void Update(float deltaTime) {}
        virtual void Render() {}

        GameObject* GetGameObject();

    protected:
        GameObject* gameObject;
    };
}