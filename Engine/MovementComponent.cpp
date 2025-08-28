#include "pch.h"
#include "MovementComponent.h"
#include "InputComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include <iostream>

namespace GameEngine
{
    MovementComponent::MovementComponent(GameObject* gameObject)
        : Component(gameObject)
    {
        transform = gameObject->GetComponent<TransformComponent>();
        input = gameObject->GetComponent<InputComponent>();

        if (transform == nullptr) {
            std::cout << "MovementComponent requires TransformComponent" << std::endl;
            gameObject->RemoveComponent(this);
            return;
        }
        if (input == nullptr) {
            std::cout << "MovementComponent requires InputComponent" << std::endl;
            gameObject->RemoveComponent(this);
            return;
        }
    }

    void MovementComponent::Update(float deltaTime)
    {
        if (transform == nullptr || input == nullptr) return;

        float horizontal = input->GetHorizontalAxis();
        float vertical = input->GetVerticalAxis();

        // Отладочный вывод
        if (horizontal != 0 || vertical != 0)
        {
            std::cout << "Movement input: " << horizontal << ", " << vertical << std::endl;
        }

        if (horizontal != 0 || vertical != 0)
        {
            Vector2Df movement(horizontal * speed * deltaTime,
                vertical * speed * deltaTime);
            transform->MoveBy(movement);

            // Отладочный вывод позиции
            auto pos = transform->GetWorldPosition();
            std::cout << "Player position: " << pos.x << ", " << pos.y << std::endl;
        }
    }

    void MovementComponent::Render()
    {
        // Пустая реализация
    }
}