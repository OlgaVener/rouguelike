#include "Player.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"

namespace RoguelikeGame
{
    Player::Player()
    {
        //Создаём объект и отрисовываем
        gameObject = GameEngine::GameWorld::Instance()->CreateGameObject();
        auto playerRenderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();

        //Добавляем коллизию
        auto collider = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();

        //Добавляем текстуру для рендера и задаём размер
        playerRenderer->SetTexture(GameEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
        playerRenderer->SetPixelSize(32, 32);

        //Добавляем и настраиваем камеру
        auto playerCamera = gameObject->AddComponent<GameEngine::CameraComponent>();
        playerCamera->SetWindow(&GameEngine::RenderSystem::Instance()->GetMainWindow());
        playerCamera->SetBaseResolution(1280, 720);

        //Настройка управления объектом
        auto playerInput = gameObject->AddComponent<GameEngine::InputComponent>();

        //движение и его скорость
        //auto movement = gameObject->AddComponent<GameEngine::MovementComponent>();
        //movement->SetSpeed(400.f);

        //Трансформация, поворот и размеры объекта
        auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
        transform->RotateBy(90.f);
        transform->MoveBy({ 1.f, 0.f });

        //Текущие параметры трансформации
        auto test = GameEngine::GameWorld::Instance()->CreateGameObject();
        auto testTransform = test->GetComponent<GameEngine::TransformComponent>();
        testTransform->SetParent(transform);

        transform->RotateBy(-90.f);
        transform->Print();
        testTransform->Print();

    }

    //Получение игрового объекта
    GameEngine::GameObject* Player::GetGameObject()
    {
        return gameObject;
    }
}