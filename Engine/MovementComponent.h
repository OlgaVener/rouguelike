#pragma once
#include "pch.h"
#include "Component.h"

namespace GameEngine
{
    // Предварительное объявление классов
    class InputComponent;
    class TransformComponent;

    class MovementComponent : public Component
    {
    public:
        MovementComponent(GameObject* gameObject);
        void Update(float deltaTime) override;
        void Render() override;

        void SetSpeed(float newSpeed) { speed = newSpeed; }
        float GetSpeed() const { return speed; }

    private:
        float speed = 200.f;
        InputComponent* input = nullptr;
        TransformComponent* transform = nullptr;
    };
}