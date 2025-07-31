#pragma once

#include "ColliderComponent.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"
#include "GameObject.h"
#include <SFML/Graphics/Rect.hpp>

namespace GameEngine
{
    class SpriteColliderComponent : public ColliderComponent
    {
    public:
        SpriteColliderComponent(GameObject* gameObject);
        ~SpriteColliderComponent();

        void Update(float deltaTime) override;
        void Render() override;

        // Реализация GetBounds
        const sf::FloatRect& GetBounds() const override;

    private:
        sf::FloatRect bounds;
    };
}
