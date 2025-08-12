#include "Floor.h"
#include <iostream>

RoguelikeGame::Floor::Floor(const GameEngine::Vector2D<float>& position, int textureMapIndex)
    : gameObject(nullptr)
{
    gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("Floor");

    auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
    transform->SetWorldPosition(position);

    // Получаем текстуру с проверкой
    const sf::Texture* texture = GameEngine::ResourceSystem::Instance()
        ->GetTextureMapElementShared("floor.png", textureMapIndex);

    if (!texture)
    {
        std::cerr << "ERROR: Failed to get floor texture with index " << textureMapIndex << std::endl;
        return;
    }

    // Проверяем размер текстуры
    if (texture->getSize().x == 0 || texture->getSize().y == 0)
    {
        std::cerr << "ERROR: Invalid floor texture size for index " << textureMapIndex << std::endl;
        return;
    }

    auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
    renderer->SetTexture(*texture);
    renderer->SetPixelSize(128, 128);
}