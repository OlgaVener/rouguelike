#include "Wall.h"

RoguelikeGame::Wall::Wall(const GameEngine::Vector2Df position, int textureMapIndex)
    : gameObject(nullptr)
{
    gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("Wall");
    auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
    transform->SetWorldPosition(position);

    auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
    renderer->SetTexture(*GameEngine::ResourceSystem::Instance()->GetTextureMapElementShared("level_walls", textureMapIndex));
    renderer->SetPixelSize(128, 128);

    auto rigidbody = gameObject->AddComponent<GameEngine::RigidbodyComponent>();
    rigidbody->SetKinematic(true);

    auto collider = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();
}