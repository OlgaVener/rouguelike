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

        // ���������� ������
        virtual bool IsTrigger() const { return false; }
        virtual void InTriggerEnter(ColliderComponent* other) {}
    };
}
