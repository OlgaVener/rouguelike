#include "Player.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"

namespace RoguelikeGame
{
    Player::Player()
    {
        gameObject = GameEngine::GameWorld::Instance()->CreateGameObject();
        auto playerRenderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();

        auto collider = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();

        // اàمًَوàهى ٍهêًٌٍََ
        playerRenderer->SetTexture(*GameEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
        playerRenderer->SetPixelSize(32, 32);

        //سٌٍàيàâëèâàهى ïîçèِè‏ êàىهًû
        auto playerCamera = gameObject->AddComponent<GameEngine::CameraComponent>();
        playerCamera->SetWindow(&GameEngine::RenderSystem::Instance()->GetMainWindow());
        playerCamera->SetBaseResolution(1280, 720);

        auto playerInput = gameObject->AddComponent<GameEngine::InputComponent>();

        auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
        transform->RotateBy(90.f);
        transform->MoveBy({ 1.f, 0.f });

        auto test = GameEngine::GameWorld::Instance()->CreateGameObject();
        auto testTransform = test->GetComponent<GameEngine::TransformComponent>();
        testTransform->SetParent(transform);

        transform->RotateBy(-90.f);
        transform->Print();
        testTransform->Print();

    }

    GameEngine::GameObject* Player::GetGameObject()
    {
        return gameObject;
    }
}