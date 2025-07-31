#pragma once

#include "ColliderComponent.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
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

    private:
        sf::FloatRect bounds;
    };
}