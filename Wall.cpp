#include "Wall.h"
#include <iostream>
#include "SpriteRendererComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "GameWorld.h"
#include "ResourceSystem.h"

RoguelikeGame::Wall::Wall(const GameEngine::Vector2Df position, int textureMapIndex)
    : gameObject(nullptr)
{
    //Создаём объект и устанавливаем позицию
    gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("Wall");
    auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
    transform->SetWorldPosition(position);

    //Загрузка текстуры по заданному индексу
    auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
    renderer->SetTexture(GameEngine::ResourceSystem::Instance()->GetTextureMapElementShared("walls", textureMapIndex));
    renderer->SetPixelSize(128, 128);

    //Физика объекта
    auto rigidbody = gameObject->AddComponent<GameEngine::RigidbodyComponent>();
    rigidbody->SetKinematic(true);

    //Коллизия объекта
    gameObject->AddComponent<GameEngine::SpriteColliderComponent>();
}
