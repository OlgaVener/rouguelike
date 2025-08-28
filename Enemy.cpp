#include "Enemy.h"
#include "FollowComponent.h"
#include <SpriteColliderComponent.h>

namespace RoguelikeGame
{
    EnemyAI::EnemyAI(const GameEngine::Vector2Df& position, GameEngine::GameObject* player)
    {
        gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("AI");
        auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
        transform->SetWorldPosition(position);

        // СОЗДАЕМ ТЕКСТУРУ ДЛЯ ВРАГА
        sf::Texture* texture = new sf::Texture();
        if (texture->loadFromFile("Resources/Textures/ai.png")) {
            std::cout << "Enemy texture loaded successfully" << std::endl;
        }
        else {
            // Fallback: если файл не найден, создаем простую текстуру
            std::cout << "Enemy texture not found, creating test texture" << std::endl;
            if (texture->create(100, 100)) {
                sf::Image image;
                image.create(100, 100, sf::Color::Red); // Красный враг для видимости

                // Добавляем отличительные features
                for (int i = 0; i < 100; i++) {
                    image.setPixel(i, 50, sf::Color::Yellow);    // Горизонтальная линия
                    image.setPixel(50, i, sf::Color::Yellow);    // Вертикальная линия
                }
                texture->loadFromImage(image);
            }
        }

        auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
        renderer->SetTexture(texture);
        renderer->SetPixelSize(42, 42);

        // Преследование игрока
        auto follower = gameObject->AddComponent<GameEngine::FollowComponent>();
        follower->SetTarget(player);
        follower->SetSpeed(220.f);

        // Физика
        auto rigidbody = gameObject->AddComponent<GameEngine::RigidbodyComponent>();
        rigidbody->SetKinematic(false);

        // Коллайдер
        auto collider = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();

        std::cout << "Enemy created at: (" << position.x << ", " << position.y << ")" << std::endl;
    }
}