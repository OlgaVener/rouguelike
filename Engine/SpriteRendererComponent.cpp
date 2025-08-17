#include "pch.h"
#include "GameObject.h"
#include "Logger.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"

namespace GameEngine
{
    // ��������������� ������� ��� ����������� ����� ������ ��������
    template <typename T1, typename T2>
    T1 Convert(const T2& vec)
    {
        return T1(vec.x, vec.y);
    }

    // ����������� ����������
    SpriteRendererComponent::SpriteRendererComponent(GameObject* gameObject)
        : Component(gameObject),               // ������������� �������� ������
        sprite(new sf::Sprite()),              // �������� ������ ������� SFML
        transform(gameObject->GetComponent<TransformComponent>()), // ��������� ���������� �������������
        scale(1.f, -1.f),                      // ������������� �������� (��� Y �������������)
        isFlipX(false),                         // ���� ��������� �� X
        isFlipY(false)                         // ���� ��������� �� Y
    {
        if (!sprite) {
            throw std::runtime_error("Failed to create sprite!");
        }
        std::cout << "SpriteRenderer created for: " << gameObject->GetName() << std::endl;
        sprite->setScale(scale.x, scale.y);     // ��������� ���������� ��������
    }

    // ���������� ����������
    SpriteRendererComponent::~SpriteRendererComponent()
    {
        delete sprite;  // ������������ ������ �������
    }

    // ��������� �������� ��� �������
    void SpriteRendererComponent::SetTexture(const sf::Texture* newTexture) {
        if (!newTexture) {
            LOG_ERROR("Attempt to set null texture for: " + gameObject->GetName());
            return;
        }

        if (!sprite) {
            LOG_ERROR("Sprite not initialized for: " + gameObject->GetName());
            return;
        }

        auto texSize = newTexture->getSize();
        LOG_INFO("Setting texture for: " + gameObject->GetName() +
            " Texture size: " + std::to_string(texSize.x) +
            "x" + std::to_string(texSize.y));

        sprite->setTexture(*newTexture, true);
        sprite->setOrigin(texSize.x * 0.5f, texSize.y * 0.5f);
    }

    // ��������� ������� ������� � ��������
    void SpriteRendererComponent::SetPixelSize(int newWidth, int newHeight)
    {
        if (sprite && sprite->getTexture())
        {
            auto textureSize = sprite->getTexture()->getSize();
            if (textureSize.x > 0 && textureSize.y > 0)
            {
                // ���������� �������� ��� ���������� ������� �������
                scale.x = static_cast<float>(newWidth) / textureSize.x;
                scale.y = static_cast<float>(newHeight) / textureSize.y;

                // ���������� �������� � ������ ������������� � ���������
                auto transformScale = Convert<sf::Vector2f, Vector2Df>(transform->GetWorldScale());
                sprite->setScale({
                    scale.x * transformScale.x * (isFlipX ? -1.f : 1.f),
                    scale.y * transformScale.y * (isFlipY ? -1.f : 1.f)
                    });
            }
        }
    }

    // ���������� ��������� ������� (���������� ������ ����)
    void SpriteRendererComponent::Update(float deltaTime)
    {
        if (transform && sprite)
        {
            // ������������� ������� � �������������� �������
            sprite->setPosition(Convert<sf::Vector2f, Vector2Df>(transform->GetWorldPosition()));
        }
    }

    // ��������� �������
    void SpriteRendererComponent::Render()
    {
        if (sprite && transform && sprite->getTexture())
        {
            // ��������� �������� �� �������������
            sprite->setRotation(transform->GetWorldRotation());

            // ���������� �������� � ������ ������������� � ���������
            auto transformScale = Convert<sf::Vector2f, Vector2Df>(transform->GetWorldScale());
            sprite->setScale({
                scale.x * transformScale.x * (isFlipX ? -1.f : 1.f),
                scale.y * transformScale.y * (isFlipY ? -1.f : 1.f)
                });

            // �������� ������� � ������� ����������
            RenderSystem::Instance()->Render(*sprite);
        }
    }

    // ��������� ��������� �� SFML ������
    const sf::Sprite* SpriteRendererComponent::GetSprite() const
    {
        return sprite;
    }

    // ��������� ������� �� �����������
    void SpriteRendererComponent::FlipX(bool flip)
    {
        if (sprite && flip != isFlipX)
        {
            isFlipX = flip;
            auto currentScale = sprite->getScale();
            sprite->setScale(-currentScale.x, currentScale.y);  // �������� �������� �� X
        }
    }

    // ��������� ������� �� ���������
    void SpriteRendererComponent::FlipY(bool flip)
    {
        if (sprite && flip != isFlipY)
        {
            isFlipY = flip;
            auto currentScale = sprite->getScale();
            sprite->setScale(currentScale.x, -currentScale.y);  // �������� �������� �� Y
        }
    }
}