#include "pch.h"
#include "PhysicsSystem.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "ColliderComponent.h"
#include "RenderSystem.h"


namespace GameEngine
{
    PhysicsSystem* PhysicsSystem::Instance()
    {
        static PhysicsSystem physicsSystem;
        return &physicsSystem;
    }

    float PhysicsSystem::GetFixedDeltaTime() const
    {
        return fixedDeltaTime;
    }

    void PhysicsSystem::Update()
    {
        sf::RenderWindow& window = RenderSystem::Instance()->GetMainWindow();
        sf::Vector2u winSize = window.getSize();

        for (auto* movingCollider : colliders)
        {
            auto* rb = movingCollider->GetGameObject()->GetComponent<RigidbodyComponent>();
            if (!rb || rb->GetKinematic()) continue; // стены не двигаем

            auto* transform = movingCollider->GetGameObject()->GetComponent<TransformComponent>();
            sf::FloatRect bounds = movingCollider->GetBounds();

            // Двигаем по X
            Vector2Df moveX(rb->GetLinearVelocity().x * GetFixedDeltaTime(), 0.f);
            transform->MoveBy(moveX);

            for (auto* staticCollider : colliders)
            {
                if (staticCollider == movingCollider) continue;
                auto* staticRb = staticCollider->GetGameObject()->GetComponent<RigidbodyComponent>();
                if (!staticRb || !staticRb->GetKinematic()) continue; // только стены

                sf::FloatRect intersection;
                if (movingCollider->GetBounds().intersects(staticCollider->GetBounds(), intersection))
                {
                    ResolveCollision(transform, movingCollider, staticCollider, intersection, 1.f);
                }
            }

            // Двигаем по Y
            Vector2Df moveY(0.f, rb->GetLinearVelocity().y * GetFixedDeltaTime());
            transform->MoveBy(moveY);

            for (auto* staticCollider : colliders)
            {
                if (staticCollider == movingCollider) continue;
                auto* staticRb = staticCollider->GetGameObject()->GetComponent<RigidbodyComponent>();
                if (!staticRb || !staticRb->GetKinematic()) continue; // только стены

                sf::FloatRect intersection;
                if (movingCollider->GetBounds().intersects(staticCollider->GetBounds(), intersection))
                {
                    ResolveCollision(transform, movingCollider, staticCollider, intersection, 1.f);
                }
            }

            // Ограничение по границам уровня
            bounds = movingCollider->GetBounds();
            float levelLeft = 0.f;
            float levelTop = 0.f;
            float levelRight = 1280.f;
            float levelBottom = 704.f;

            if (bounds.left < levelLeft) transform->MoveBy(levelLeft - bounds.left, 0.f);
            if (bounds.top < levelTop) transform->MoveBy(0.f, levelTop - bounds.top);
            if (bounds.left + bounds.width > levelRight) transform->MoveBy(levelRight - (bounds.left + bounds.width), 0.f);
            if (bounds.top + bounds.height > levelBottom) transform->MoveBy(0.f, levelBottom - (bounds.top + bounds.height));
        }

        // Обработка триггеров (оставляем как есть)
        for (auto it = triggersEnteredPair.begin(); it != triggersEnteredPair.end();)
        {
            auto* first = it->first;
            auto* second = it->second;

            if (!first->GetBounds().intersects(second->GetBounds()))
            {
                Trigger trigger(first, second);
                first->OnTriggerExit(trigger);
                second->OnTriggerExit(trigger);
                it = triggersEnteredPair.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }


    void PhysicsSystem::MoveWithCollision(RigidbodyComponent* rb, Vector2Df desiredMove)
    {
        if (!rb) return;
        auto* transform = rb->GetGameObject()->GetComponent<TransformComponent>();
        auto* collider = rb->GetGameObject()->GetComponent<ColliderComponent>();
        if (!transform || !collider) return;

        // --- Движение по X ---
        float moveX = desiredMove.x;
        transform->MoveBy(Vector2Df(moveX, 0.f));

        for (auto* wallCollider : colliders)
        {
            if (wallCollider == collider) continue;

            auto* wallRb = wallCollider->GetGameObject()->GetComponent<RigidbodyComponent>();
            if (!wallRb || !wallRb->GetKinematic()) continue; // только стены

            sf::FloatRect playerBounds = collider->GetBounds();
            sf::FloatRect wallBounds = wallCollider->GetBounds();
            sf::FloatRect intersection;

            if (playerBounds.intersects(wallBounds, intersection))
            {
                // Отталкиваем по X
                if (playerBounds.left < wallBounds.left)
                    transform->MoveBy(-intersection.width, 0.f);
                else
                    transform->MoveBy(intersection.width, 0.f);
            }
        }

        // --- Движение по Y ---
        float moveY = desiredMove.y;
        transform->MoveBy(Vector2Df(0.f, moveY));

        for (auto* wallCollider : colliders)
        {
            if (wallCollider == collider) continue;

            auto* wallRb = wallCollider->GetGameObject()->GetComponent<RigidbodyComponent>();
            if (!wallRb || !wallRb->GetKinematic()) continue; // только стены

            sf::FloatRect playerBounds = collider->GetBounds();
            sf::FloatRect wallBounds = wallCollider->GetBounds();
            sf::FloatRect intersection;

            if (playerBounds.intersects(wallBounds, intersection))
            {
                // Отталкиваем по Y
                if (playerBounds.top < wallBounds.top)
                    transform->MoveBy(0.f, -intersection.height);
                else
                    transform->MoveBy(0.f, intersection.height);
            }
        }

        // --- Ограничение по границам уровня ---
        auto bounds = collider->GetBounds();
        float levelLeft = 0.f;
        float levelTop = 0.f;
        float levelRight = 1280.f;
        float levelBottom = 704.f;

        if (bounds.left < levelLeft) transform->MoveBy(levelLeft - bounds.left, 0.f);
        if (bounds.top < levelTop) transform->MoveBy(0.f, levelTop - bounds.top);
        if (bounds.left + bounds.width > levelRight) transform->MoveBy(levelRight - (bounds.left + bounds.width), 0.f);
        if (bounds.top + bounds.height > levelBottom) transform->MoveBy(0.f, levelBottom - (bounds.top + bounds.height));
    }

    void PhysicsSystem::Subscribe(ColliderComponent* collider)
    {
        colliders.push_back(collider);
    }

    void PhysicsSystem::Unsubscribe(ColliderComponent* collider)
    {
        colliders.erase(std::remove(colliders.begin(), colliders.end(), collider), colliders.end());
    }

    void PhysicsSystem::ResolveCollision(TransformComponent* movingTransform,
        ColliderComponent* movingCollider,
        ColliderComponent* staticCollider,
        const sf::FloatRect& intersection,
        float moveFactor)
    {
        if (intersection.width > intersection.height)
        {
            // Коллизия по Y
            if (movingCollider->GetBounds().top < staticCollider->GetBounds().top)
                movingTransform->MoveBy(0.f, -intersection.height * moveFactor);
            else
                movingTransform->MoveBy(0.f, intersection.height * moveFactor);
        }
        else
        {
            // Коллизия по X
            if (movingCollider->GetBounds().left < staticCollider->GetBounds().left)
                movingTransform->MoveBy(-intersection.width * moveFactor, 0.f);
            else
                movingTransform->MoveBy(intersection.width * moveFactor, 0.f);
        }
    }
}
