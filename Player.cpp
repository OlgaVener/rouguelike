#include "Player.h"
#include "ResourceSystem.h"

namespace RoguelikeGame
{
    Player::Player()
    {
        gameObject = GameEngine::GameWorld::Instance()->CreateGameObject();
        auto playerRenderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();

        // «агружаем текстуру (убедитесь, что "ball" загружена в ResourceSystem)
        playerRenderer->SetTexture(*GameEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
        playerRenderer->SetPixelSize(32, 32);

        auto playerCamera = gameObject->AddComponent<GameEngine::CameraComponent>();
        playerCamera->SetWindow(&GameEngine::RenderSystem::Instance()->GetMainWindow());
        playerCamera->SetBaseResolution(1280, 720);

        auto playerInput = gameObject->AddComponent<GameEngine::InputComponent>();
    }

    GameEngine::GameObject* Player::GetGameObject()
    {
        return gameObject;
    }
}