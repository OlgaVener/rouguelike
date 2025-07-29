#include "pch.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"

namespace GameEngine
{
    template <typename T1, typename T2>
    T1 Convert(const T2& vec)
    {
        return T1(vec.x, vec.y);
    }

    SpriteRendererComponent::SpriteRendererComponent(GameObject* gameObject) : Component(gameObject)
    {
        sprite = new sf::Sprite();
        scale = { 1, -1 };
        sprite->setScale({ 1, -1 });
        transform = gameObject->GetComponent<TransformComponent>();
    }

    SpriteRendererComponent::~SpriteRendererComponent()
    {
        if (sprite != nullptr)
        {
            delete sprite;
        }
    }


    void SpriteRendererComponent::Update(float deltaTime) 
    {
        if (transform && sprite) 
        {
            auto pos = transform->GetWorldPosition();
            sprite->setPosition(pos.x, pos.y);
        }
    }

    void SpriteRendererComponent::Render()
    {
        if (sprite != nullptr && transform != nullptr)
        {
            sprite->setPosition(Convert<sf::Vector2f, Vector2Df>(transform->GetWorldPosition()));
            sprite->setRotation(transform->GetWorldRotation());

            auto transformScale = Convert<sf::Vector2f, Vector2Df>(transform->GetWorldScale());
            sprite->setScale({ scale.x * transformScale.x, scale.y * transformScale.y });
            RenderSystem::Instance()->Render(*sprite);
        }
    }

    const sf::Sprite* SpriteRendererComponent::GetSprite() const
    {
        return sprite;
    }

    void SpriteRendererComponent::SetTexture(const sf::Texture& newTexture)
    {
        sprite->setTexture(newTexture);
        auto textureSize = sprite->getTexture()->getSize();
        sprite->setOrigin({ 0.5f * textureSize.x, 0.5f * textureSize.y });
    }

    void SpriteRendererComponent::SetPixelSize(int newWidth, int newHeight)
    {
        auto originalSize = sprite->getTexture()->getSize();
        sprite->setScale(
            (float)newWidth / (float)originalSize.x,
            (float)newHeight / (float)originalSize.y
        );
    }

    void SpriteRendererComponent::FlipX(bool flip)
    {
        if (flip != isFlipX)
        {
            auto scale = sprite->getScale();
            sprite->setScale({ -scale.x, scale.y });
            isFlipX = flip;
        }
    }

    void SpriteRendererComponent::FlipY(bool flip)
    {
        if (flip != isFlipY)
        {
            auto scale = sprite->getScale();
            sprite->setScale({ scale.x, -scale.y });
            isFlipY = flip;
        }
    }
}