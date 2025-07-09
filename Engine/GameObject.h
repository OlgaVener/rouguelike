#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>  // Added for std::remove_if
#include "Component.h"
#include "TransformComponent.h"

namespace Engine
{
    class TransformComponent;

    class GameObject
    {
    public:
        GameObject();
        ~GameObject();

        void Update(float deltatime);
        void Render();

        template <typename T>
        T* AddComponent()
        {
            if constexpr (!std::is_base_of<Component, T>::value)
            {
                std::cout << "T must be derived from Component." << std::endl;
                return nullptr;
            }
            if constexpr (std::is_same<T, TransformComponent>::value)
            {
                if (GetComponent<TransformComponent>() != nullptr)
                {
                    std::cout << "Can't add Transform, because it will break the engine loop." << std::endl;
                    return nullptr;
                }
            }

            T* newComponent = new T(this);
            components.push_back(newComponent);
            std::cout << "Add new component: " << newComponent << std::endl;
            return newComponent;
        }

        void RemoveComponent(Component* component)  // Fixed parameter name (was 'conponent')
        {
            components.erase(std::remove_if(components.begin(), components.end(),
                [component](Component* obj) {
                    return obj == component;
                }),
                components.end());
            delete component;
            std::cout << "Deleted component";
        }

        template <typename T>
        T* GetComponent() const
        {
            for (const auto& component : components)
            {
                if (auto casted = dynamic_cast<T*>(component))
                {
                    return casted;
                }
            }
            return nullptr;
        }

    private:
        std::vector<Component*> components;
    };
}