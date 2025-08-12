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
    SpriteRendererComponent::SpriteRendererComponent(GameObject* gameObject)
        : Component(gameObject),
        sprite(new sf::Sprite()),
        transform(gameObject->GetComponent<TransformComponent>()),
        scale(1.f, -1.f),
        isFlipX(false),
        isFlipY(false)
    {
        if (!sprite)
        {
            throw std::runtime_error("Failed to create sprite!");
        }
        sprite->setScale(scale.x, scale.y);
    }

    SpriteRendererComponent::~SpriteRendererComponent()
    {
        delete sprite;  // delete безопасен с nullptr
    }

    void SpriteRendererComponent::Update(float deltaTime)
    {
        if (transform && sprite)
        {
            sprite->setPosition(Convert<sf::Vector2f, Vector2Df>(transform->GetWorldPosition()));
        }
    }

    void SpriteRendererComponent::Render()
    {
        if (sprite && transform && sprite->getTexture())
        {
            sprite->setRotation(transform->GetWorldRotation());

            auto transformScale = Convert<sf::Vector2f, Vector2Df>(transform->GetWorldScale());
            sprite->setScale({
                scale.x * transformScale.x * (isFlipX ? -1.f : 1.f),
                scale.y * transformScale.y * (isFlipY ? -1.f : 1.f)
                });

            RenderSystem::Instance()->Render(*sprite);
        }
    }

    const sf::Sprite* SpriteRendererComponent::GetSprite() const
    {
        return sprite;
    }
  
    void SpriteRendererComponent::SetTexture(const sf::Texture& newTexture)
    {
        if (!sprite)
        {
            return;
        }

        sprite->setTexture(newTexture, true);

        // Проверяем, что текстура установлена
        const sf::Texture* texture = sprite->getTexture();
        if (!texture)
        {
            // Ошибка: текстура не установлена
            return;
        }

        // Устанавливаем origin в центр текстуры
        sf::Vector2u textureSize = texture->getSize();
        sprite->setOrigin(textureSize.x * 0.5f, textureSize.y * 0.5f);
    }

    void SpriteRendererComponent::SetPixelSize(int newWidth, int newHeight)
    {
        if (sprite && sprite->getTexture())
        {
            auto textureSize = sprite->getTexture()->getSize();
            if (textureSize.x > 0 && textureSize.y > 0)
            {
                scale.x = static_cast<float>(newWidth) / textureSize.x;
                scale.y = static_cast<float>(newHeight) / textureSize.y;

                auto transformScale = Convert<sf::Vector2f, Vector2Df>(transform->GetWorldScale());
                sprite->setScale({
                    scale.x * transformScale.x * (isFlipX ? -1.f : 1.f),
                    scale.y * transformScale.y * (isFlipY ? -1.f : 1.f)
                    });
            }
        }
    }

    void SpriteRendererComponent::FlipX(bool flip)
    {
        if (sprite && flip != isFlipX)
        {
            isFlipX = flip;
            auto currentScale = sprite->getScale();
            sprite->setScale(-currentScale.x, currentScale.y);
        }
    }

    void SpriteRendererComponent::FlipY(bool flip)
    {
        if (sprite && flip != isFlipY)
        {
            isFlipY = flip;
            auto currentScale = sprite->getScale();
            sprite->setScale(currentScale.x, -currentScale.y);
        }
    }
}