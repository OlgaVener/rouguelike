#include "pch.h"
#include "SpriteColliderComponent.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"

namespace GameEngine
{
    SpriteColliderComponent::SpriteColliderComponent(GameObject* gameObject)
        : ColliderComponent(gameObject)
    {
    }

    SpriteColliderComponent::~SpriteColliderComponent() {}

    void SpriteColliderComponent::Update(float deltaTime)
    {
        auto spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
        auto transform = gameObject->GetComponent<TransformComponent>();

        if (spriteRenderer && spriteRenderer->GetSprite() && transform)
        {
            const sf::Sprite* sprite = spriteRenderer->GetSprite();
            bounds = sprite->getGlobalBounds();
        }
    }

    void SpriteColliderComponent::Render()
    {
        auto* spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
        if (!spriteRenderer || !spriteRenderer->GetSprite()) return;

        const sf::Sprite* sprite = spriteRenderer->GetSprite();
        sf::FloatRect localBounds = sprite->getLocalBounds();

        sf::RectangleShape rectangle;
        rectangle.setSize({ localBounds.width, localBounds.height });
        rectangle.setOrigin(sprite->getOrigin());
        rectangle.setPosition(sprite->getPosition());
        rectangle.setRotation(sprite->getRotation());
        rectangle.setScale(sprite->getScale());
        rectangle.setFillColor(sf::Color::Transparent);
        rectangle.setOutlineColor(sf::Color::White);
        rectangle.setOutlineThickness(2.f);

        RenderSystem::Instance()->Render(rectangle);
    }

    const sf::FloatRect& SpriteColliderComponent::GetBounds() const
    {
        return bounds;
    }
}