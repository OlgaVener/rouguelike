#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Component.h"

namespace Engine {
    class GameObject {
    public:
        virtual ~GameObject() = default;
        virtual void draw(sf::RenderWindow& window) const = 0;
        virtual sf::FloatRect getBounds() const = 0;
        virtual void update(float deltaTime) {}

        template <typename T>
        T* GetComponent() {
            for (auto& component : components) {
                if (auto ptr = dynamic_cast<T*>(component.get())) {
                    return ptr;
                }
            }
            return nullptr;
        }

    protected:
        std::vector<std::unique_ptr<Component>> components;
    };
}