#include "Wall.h"
#include "SpriteRendererComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "GameWorld.h"
#include "ResourceSystem.h"
#include "Logger.h"

namespace RoguelikeGame
{
    Wall::~Wall()
    {
        // Если texture динамический
        if (texture)
        {
            delete texture;
            texture = nullptr;
        }
    }

    Wall::Wall(const GameEngine::Vector2Df position, int textureMapIndex)
    {
        gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("Wall");
        auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
        transform->SetWorldPosition(position);
        transform->SetWorldScale(GameEngine::Vector2Df(1.f, 1.f));

        // Спрайт
        auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
        texture = new sf::Texture();
        if (!texture->loadFromFile("Resources/Textures/walls.png"))
        {
            std::cout << "Wall texture not found, using fallback" << std::endl;
            texture->create(64, 64);
        }
        renderer->SetTexture(texture);
        renderer->SetPixelSize(64, 64);

        // Коллайдер
        auto collider = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();
        GameEngine::PhysicsSystem::Instance()->Subscribe(collider);

        // Rigidbody
        auto rigidbody = gameObject->AddComponent<GameEngine::RigidbodyComponent>();
        rigidbody->SetKinematic(true);
    }
}