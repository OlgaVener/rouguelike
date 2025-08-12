#include "Wall.h"
#include <iostream>

RoguelikeGame::Wall::Wall(const GameEngine::Vector2Df position, int textureMapIndex)
    : gameObject(nullptr)
{
    gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("Wall");
    auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
    transform->SetWorldPosition(position);

    // Получаем текстуру с проверкой
    const sf::Texture* texture = GameEngine::ResourceSystem::Instance()
        ->GetTextureMapElementShared("walls.png", textureMapIndex);

    if (!texture)
    {
        std::cerr << "ERROR: Failed to get wall texture with index " << textureMapIndex << std::endl;
        return;
    }

    // Проверяем размер текстуры
    if (texture->getSize().x == 0 || texture->getSize().y == 0)
    {
        std::cerr << "ERROR: Invalid wall texture size for index " << textureMapIndex << std::endl;
        return;
    }

    auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
    renderer->SetTexture(*texture);
    renderer->SetPixelSize(128, 128);

    auto rigidbody = gameObject->AddComponent<GameEngine::RigidbodyComponent>();
    rigidbody->SetKinematic(true);

    auto collider = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();
}