#include "pch.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"

namespace GameEngine
{
    // Вспомогательная функция для конвертации между типами векторов
    template <typename T1, typename T2>
    T1 Convert(const T2& vec)
    {
        return T1(vec.x, vec.y);
    }

    // Конструктор компонента
    SpriteRendererComponent::SpriteRendererComponent(GameObject* gameObject)
        : Component(gameObject),               // Инициализация базового класса
        sprite(new sf::Sprite()),              // Создание нового спрайта SFML
        transform(gameObject->GetComponent<TransformComponent>()), // Получение компонента трансформации
        scale(1.f, -1.f),                      // Инициализация масштаба (ось Y инвертирована)
        isFlipX(false),                         // Флаг отражения по X
        isFlipY(false)                         // Флаг отражения по Y
    {
        if (!sprite)
        {
            throw std::runtime_error("Failed to create sprite!");
        }
        sprite->setScale(scale.x, scale.y);     // Установка начального масштаба
    }

    // Деструктор компонента
    SpriteRendererComponent::~SpriteRendererComponent()
    {
        delete sprite;  // Освобождение памяти спрайта
    }

    // Установка текстуры для спрайта
    void SpriteRendererComponent::SetTexture(const sf::Texture* newTexture)
    {
        if (!sprite || !newTexture)  // Проверка валидности указателей
        {
            return;
        }

        sprite->setTexture(*newTexture, true);  // Применение текстуры

        // Установка центра спрайта в центр текстуры
        auto textureSize = newTexture->getSize();
        sprite->setOrigin(textureSize.x * 0.5f, textureSize.y * 0.5f);
    }

    // Установка размера спрайта в пикселях
    void SpriteRendererComponent::SetPixelSize(int newWidth, int newHeight)
    {
        if (sprite && sprite->getTexture())
        {
            auto textureSize = sprite->getTexture()->getSize();
            if (textureSize.x > 0 && textureSize.y > 0)
            {
                // Вычисление масштаба для достижения нужного размера
                scale.x = static_cast<float>(newWidth) / textureSize.x;
                scale.y = static_cast<float>(newHeight) / textureSize.y;

                // Применение масштаба с учетом трансформации и отражений
                auto transformScale = Convert<sf::Vector2f, Vector2Df>(transform->GetWorldScale());
                sprite->setScale({
                    scale.x * transformScale.x * (isFlipX ? -1.f : 1.f),
                    scale.y * transformScale.y * (isFlipY ? -1.f : 1.f)
                    });
            }
        }
    }

    // Обновление состояния спрайта (вызывается каждый кадр)
    void SpriteRendererComponent::Update(float deltaTime)
    {
        if (transform && sprite)
        {
            // Синхронизация позиции с трансформацией объекта
            sprite->setPosition(Convert<sf::Vector2f, Vector2Df>(transform->GetWorldPosition()));
        }
    }

    // Отрисовка спрайта
    void SpriteRendererComponent::Render()
    {
        if (sprite && transform && sprite->getTexture())
        {
            // Установка поворота из трансформации
            sprite->setRotation(transform->GetWorldRotation());

            // Обновление масштаба с учетом трансформации и отражений
            auto transformScale = Convert<sf::Vector2f, Vector2Df>(transform->GetWorldScale());
            sprite->setScale({
                scale.x * transformScale.x * (isFlipX ? -1.f : 1.f),
                scale.y * transformScale.y * (isFlipY ? -1.f : 1.f)
                });

            // Передача спрайта в систему рендеринга
            RenderSystem::Instance()->Render(*sprite);
        }
    }

    // Получение указателя на SFML спрайт
    const sf::Sprite* SpriteRendererComponent::GetSprite() const
    {
        return sprite;
    }

    // Отражение спрайта по горизонтали
    void SpriteRendererComponent::FlipX(bool flip)
    {
        if (sprite && flip != isFlipX)
        {
            isFlipX = flip;
            auto currentScale = sprite->getScale();
            sprite->setScale(-currentScale.x, currentScale.y);  // Инверсия масштаба по X
        }
    }

    // Отражение спрайта по вертикали
    void SpriteRendererComponent::FlipY(bool flip)
    {
        if (sprite && flip != isFlipY)
        {
            isFlipY = flip;
            auto currentScale = sprite->getScale();
            sprite->setScale(currentScale.x, -currentScale.y);  // Инверсия масштаба по Y
        }
    }
}