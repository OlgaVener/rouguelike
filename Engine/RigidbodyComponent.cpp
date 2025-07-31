#include "pch.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "PhysicsSystem.h"


using namespace GameEngine;

RigidbodyComponent::RigidbodyComponent(GameObject* gameObject)
    : Component(gameObject)
{
    transform = gameObject->GetComponent<TransformComponent>();
}

void RigidbodyComponent::Update(float deltaTime)
{
    transform->MoveBy(linearVelocity);
    transform->RotateBy(angleVelocity);

    linearVelocity = (1.f - linearDamping * deltaTime) * linearVelocity;
    angleVelocity = (1.f - angleDamping * deltaTime) * angleVelocity;

    if (std::abs(linearVelocity.x) < 0.001f)
        linearVelocity.x = 0.f;
    if (std::abs(linearVelocity.y) < 0.001f)
        linearVelocity.y = 0.f;
    if (std::abs(angleVelocity) < 0.001f)
        angleVelocity = 0.f;
}

void RigidbodyComponent::Render()
{
}

void RigidbodyComponent::SetLinearVelocity(Vector2Df newLinearVelocity)
{
    linearVelocity = newLinearVelocity;
}

void RigidbodyComponent::AddLinearVelocity(Vector2Df linearOffset)
{
    linearVelocity = linearVelocity + linearOffset;
}

Vector2Df RigidbodyComponent::GetLinearVelocity() const
{
    return linearVelocity;
}

void RigidbodyComponent::SetAngleVelocity(float newAngleVelocity)
{
    angleVelocity = newAngleVelocity;
}

void RigidbodyComponent::AddAngleVelocity(float angleOffset)
{
    angleVelocity += angleOffset;
}

float RigidbodyComponent::GetAngleVelocity() const
{
    return angleVelocity;
}

void RigidbodyComponent::SetLinearDamping(float newLinearDamping)
{
    linearDamping = newLinearDamping;
}

float RigidbodyComponent::GetLinearDamping() const
{
    return linearDamping;
}

void GameEngine::RigidbodyComponent::SetAngleDamping(float newAngleDamping)
{
    angleDamping = newAngleDamping;
}

float RigidbodyComponent::GetAngleDamping() const
{
    return angleDamping;
}

void RigidbodyComponent::SetKinematic(bool newIsKinematic)
{
    IsKinematic = newIsKinematic;
}

bool RigidbodyComponent::GetKinematic() const
{
    return IsKinematic;
}
