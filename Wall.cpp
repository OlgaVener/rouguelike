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
        if (texture) {
            delete texture;
            texture = nullptr;
        }
    }

    Wall::Wall(const GameEngine::Vector2Df position, int textureMapIndex)
        : texture(nullptr)
    {
        gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("Wall");
        auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
        transform->SetWorldPosition(position);
        transform->SetWorldScale(GameEngine::Vector2Df(1.f, 1.f));

        texture = new sf::Texture();

        // Пробуем загрузить настоящую текстуру
        if (!texture->loadFromFile("Resources/Textures/walls.png")) {
            std::cout << "Wall texture not found, using fallback" << std::endl;
            if (texture->create(128, 128)) {
                sf::Image image;
                image.create(128, 128, sf::Color::Cyan);
                texture->loadFromImage(image);
            }
        }

        auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
        renderer->SetTexture(texture);
        renderer->SetPixelSize(128, 128);

        auto collider = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();
        auto rigidbody = gameObject->AddComponent<GameEngine::RigidbodyComponent>();
        rigidbody->SetKinematic(true);
    }
}