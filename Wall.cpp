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

        std::string texturePath;

        switch (textureMapIndex)
        {
        case 0:  texturePath = "Resources/Textures/wall_top.png"; break;
        case 1:  texturePath = "Resources/Textures/wall_bottom.png"; break;
        case 2:  texturePath = "Resources/Textures/wall_left.png"; break;
        case 3:  texturePath = "Resources/Textures/wall_right.png"; break;
        case 4:  texturePath = "Resources/Textures/wall_corner_topleft.png"; break;
        case 5:  texturePath = "Resources/Textures/wall_corner_topright.png"; break;
        case 6:  texturePath = "Resources/Textures/wall_corner_bottomleft.png"; break;
        case 7:  texturePath = "Resources/Textures/wall_corner_bottomright.png"; break;
        default: texturePath = "Resources/Textures/wall_default.png"; break;
        }

        // --- Проверка и вывод ---
        std::cout << "[Wall] Loading texture: " << texturePath << std::endl;

        texture = new sf::Texture();
        if (!texture->loadFromFile(texturePath))
        {
            std::cerr << "[Wall] ERROR: Texture not found: " << texturePath << ", creating fallback 64x64" << std::endl;
            texture->create(64, 64); // пустая текстура вместо файла
        }

        auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
        renderer->SetTexture(texture);
        renderer->SetPixelSize(64, 64);

        auto collider = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();
        GameEngine::PhysicsSystem::Instance()->Subscribe(collider);

        auto rigidbody = gameObject->AddComponent<GameEngine::RigidbodyComponent>();
        rigidbody->SetKinematic(true);
    }
}