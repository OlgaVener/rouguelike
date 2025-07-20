#include "pch.h"
#include "GameObject.h"
#include "TransformComponent.h"


namespace GameEngine
{
    GameObject::GameObject()
    {
        AddComponent<TransformComponent>();
    }

    GameObject::~GameObject()
    {
        for (auto component : components)
        {
            delete component;
        }
        components.clear();
    }
    void GameObject::Update(float deltatime)
    {
        for (auto& component : components)
        {
            component->Update(deltatime);
        }
    }
    void GameObject::Render()
    {
        for (auto& component : components)
        {
            component->Render();
        }
    }
}