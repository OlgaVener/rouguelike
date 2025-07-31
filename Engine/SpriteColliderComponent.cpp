#include "pch.h"
#include "SpriteColliderComponent.h"

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
        if (spriteRenderer)
        {
            const sf::Sprite* sprite = spriteRenderer->GetSprite();
            if (sprite)
            {
                bounds = sprite->getGlobalBounds();
            }
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
        rectangle.setOutlineThickness(2.0f);

        RenderSystem::Instance()->Render(rectangle);
    }

    const sf::FloatRect& SpriteColliderComponent::GetBounds() const
    {
        return bounds;
    }
}
