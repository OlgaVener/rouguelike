#include "pch.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"


using namespace GameEngine;

RigidbodyComponent::RigidbodyComponent(GameObject* gameObject)
    : Component(gameObject)
{
    transform = gameObject->GetComponent<TransformComponent>();
}

void RigidbodyComponent::Update(float deltaTime)
{
    if (!transform) return;

    // Рассчитываем желаемое смещение
    Vector2Df desiredMove = linearVelocity * deltaTime;

    // Двигаем с учётом коллизий
    PhysicsSystem::Instance()->MoveWithCollision(this, desiredMove);

    // Угловая скорость (можно оставить без изменений)
    transform->RotateBy(angleVelocity * deltaTime);

    // Дампинг
    linearVelocity = (1.f - linearDamping * deltaTime) * linearVelocity;
    angleVelocity = (1.f - angleDamping * deltaTime) * angleVelocity;

    if (std::abs(linearVelocity.x) < 0.001f) linearVelocity.x = 0.f;
    if (std::abs(linearVelocity.y) < 0.001f) linearVelocity.y = 0.f;
    if (std::abs(angleVelocity) < 0.001f) angleVelocity = 0.f;
}

void PhysicsSystem::MoveWithCollision(RigidbodyComponent* rb, Vector2Df desiredMove)
{
    if (!rb) return;
    auto* transform = rb->GetGameObject()->GetComponent<TransformComponent>();
    auto* collider = rb->GetGameObject()->GetComponent<ColliderComponent>();
    if (!transform || !collider) return;

    sf::FloatRect originalBounds = collider->GetBounds();
    Vector2Df move = desiredMove;

    // Проверяем столкновения со всеми коллайдерами
    for (auto* otherCollider : colliders)
    {
        if (otherCollider == collider) continue;

        sf::FloatRect otherBounds = otherCollider->GetBounds();
        if (originalBounds.intersects(otherBounds))
        {
            // Простое разрешение по осям X и Y
            sf::FloatRect intersection;
            if (originalBounds.intersects(otherBounds, intersection))
            {
                if (intersection.width < intersection.height)
                {
                    move.x = (originalBounds.left < otherBounds.left ? -intersection.width : intersection.width);
                    move.y = 0.f;
                }
                else
                {
                    move.y = (originalBounds.top < otherBounds.top ? -intersection.height : intersection.height);
                    move.x = 0.f;
                }
            }
        }
    }

    // Двигаем трансформ с учётом коллизий
    transform->MoveBy(move);

    // Ограничение выхода за границы окна
    sf::RenderWindow& window = GameEngine::RenderSystem::Instance()->GetMainWindow();
    sf::Vector2u winSize = window.getSize();
    auto bounds = collider->GetBounds();

    if (bounds.left < 0) transform->MoveBy(-bounds.left, 0.f);
    if (bounds.top < 0) transform->MoveBy(0.f, -bounds.top);
    if (bounds.left + bounds.width > winSize.x) transform->MoveBy(-(bounds.left + bounds.width - winSize.x), 0.f);
    if (bounds.top + bounds.height > winSize.y) transform->MoveBy(0.f, -(bounds.top + bounds.height - winSize.y));
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
