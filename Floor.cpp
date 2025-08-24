#include "Floor.h"
#include <iostream>
#include "SpriteRendererComponent.h"
#include "GameWorld.h"
#include "ResourceSystem.h"

RoguelikeGame::Floor::Floor(const GameEngine::Vector2D<float>& position, int textureMapIndex)
    : gameObject(nullptr)
{
    //Создаём объект и устанавливаем позицию
    gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("Floor");
    auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
    transform->SetWorldPosition(position);

    //Загрузка текстуры по заданному индексу
    auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
    renderer->SetTexture(GameEngine::ResourceSystem::Instance()->GetTextureMapElementShared("floor", textureMapIndex));
    renderer->SetPixelSize(64, 64);
}
