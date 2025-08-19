#include "Wall.h"
#include "SpriteRendererComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "GameWorld.h"
#include "ResourceSystem.h"
#include "Logger.h"

namespace RoguelikeGame {
    Wall::Wall(const GameEngine::Vector2Df position, int textureMapIndex)
        : gameObject(nullptr)
    {
        gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("Wall");
        auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
        transform->SetWorldPosition(position);
        transform->SetWorldScale(GameEngine::Vector2Df(1.f, 1.f));

        // Загрузка текстуры с проверкой
        auto texture = GameEngine::ResourceSystem::Instance()->GetTextureMapElementShared("walls", textureMapIndex);
        if (!texture || texture->getSize().x == 0 || texture->getSize().y == 0)
        {
            LOG_ERROR("Failed to load wall texture! Index: " + std::to_string(textureMapIndex));
            // Загружаем текстуру по умолчанию
            texture = GameEngine::ResourceSystem::Instance()->GetTextureMapElementShared("default", 0);
        }

        auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
        renderer->SetTexture(texture);
        renderer->SetPixelSize(128, 128);

        auto collider = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();
        auto rigidbody = gameObject->AddComponent<GameEngine::RigidbodyComponent>();
        rigidbody->SetKinematic(true);
    }
}