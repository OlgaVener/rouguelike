#pragma once
#include "TransformComponent.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

namespace GameEngine
{
    class TransformComponent;
    class Component;

    class GameObject
    {
    public:
        GameObject();
        GameObject(std::string newName);

        ~GameObject();

        std::string GetName() const;
        void Print(int depth = 0) const;

        void Update(float deltatime);
        void Render();

        template <typename T>
        T* AddComponent()
        {
            
        }

        void RemoveComponent(Component* component)
        {
            
        }

        template <typename T>
        T* GetComponent() const
        {
            
        }

        template <typename T>
        T* GetComponentInChildren() const
        {
            T* component = GetComponent<T>();
            if (component != nullptr || children.size() == 0)
            {
                return component;
            }

            for (const auto& child : children)
            {
                T* childComponent = child->GetComponentInChildren<T>();
                if (childComponent != nullptr)
                {
                    return childComponent;
                }
            }

            return nullptr;
        }

        template <typename T>
        std::vector<T*> GetComponents() const
        {
            std::vector<T*> result;
            for (const auto& component : components)
            {
                if (auto casted = dynamic_cast<T*>(component))
                {
                    result.push_back(casted);
                }
            }
            return result;
        }

        void AddChild(GameObject* child);
        void RemoveChild(GameObject* child);

    private:
        std::string name;
        std::vector<Component*> components;
        std::vector<GameObject*> children;
    };
}