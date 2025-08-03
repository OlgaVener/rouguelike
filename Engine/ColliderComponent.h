#pragma once

#include "Component.h"
#include <SFML/Graphics/Rect.hpp>

namespace GameEngine
{
    class ColliderComponent : public Component
    {
    public:
        ColliderComponent(GameObject* gameObject) : Component(gameObject) {}
        virtual ~ColliderComponent() = default;

        virtual const sf::FloatRect& GetBounds() const = 0;

        // Триггерная логика
        virtual bool IsTrigger() const { return false; }
        virtual void OnTriggerEnter(ColliderComponent* other) {}
        virtual void OnTriggerExit(const GameEngine::Trigger& trigger);
       
        virtual void OnCollision(ColliderComponent* other) {}
    };
}
