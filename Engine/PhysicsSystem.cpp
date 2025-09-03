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
        for (size_t i = 0; i < colliders.size(); ++i)
        {
            auto* bodyA = colliders[i]->GetGameObject()->GetComponent<RigidbodyComponent>();
            if (bodyA && bodyA->GetKinematic()) continue; // стены не двигаем

            for (size_t j = 0; j < colliders.size(); ++j)
            {
                if (i == j) continue;

                sf::FloatRect intersection;
                if (colliders[i]->GetBounds().intersects(colliders[j]->GetBounds(), intersection))
                {
                    auto* aCollider = colliders[i];
                    auto* bCollider = colliders[j];

                    // Обработка триггеров
                    if (aCollider->IsTrigger() || bCollider->IsTrigger())
                    {
                        Trigger trigger(aCollider, bCollider);
                        aCollider->OnTriggerEnter(bCollider);
                        bCollider->OnTriggerEnter(aCollider);

                        triggersEnteredPair.emplace_back(aCollider, bCollider);
                        continue;
                    }

                    // Коллизия
                    auto* bBody = bCollider->GetGameObject()->GetComponent<RigidbodyComponent>();
                    auto* aTransform = aCollider->GetGameObject()->GetComponent<TransformComponent>();

                    if (bBody && bBody->GetKinematic())
                    {
                        // Двигаем только A
                        if (intersection.width > intersection.height)
                        {
                            if (aCollider->GetBounds().top < bCollider->GetBounds().top)
                                aTransform->MoveBy(0.f, -intersection.height);
                            else
                                aTransform->MoveBy(0.f, intersection.height);
                        }
                        else
                        {
                            if (aCollider->GetBounds().left < bCollider->GetBounds().left)
                                aTransform->MoveBy(-intersection.width, 0.f);
                            else
                                aTransform->MoveBy(intersection.width, 0.f);
                        }
                    }

                    // Вызов ResolveCollision (если есть реализация)
                    ResolveCollision(aTransform, aCollider, bCollider, intersection, 1.f);
                }
            }
        }

        // Ограничение выхода за пределы окна
        sf::RenderWindow& window = RenderSystem::Instance()->GetMainWindow();
        sf::Vector2u winSize = window.getSize();

        for (auto* collider : colliders)
        {
            auto* rb = collider->GetGameObject()->GetComponent<RigidbodyComponent>();
            if (!rb || rb->GetKinematic()) continue;

            auto* transform = collider->GetGameObject()->GetComponent<TransformComponent>();
            auto bounds = collider->GetBounds();

            if (bounds.left < 0) transform->MoveBy(-bounds.left, 0.f);
            if (bounds.top < 0) transform->MoveBy(0.f, -bounds.top);
            if (bounds.left + bounds.width > winSize.x)
                transform->MoveBy(-(bounds.left + bounds.width - winSize.x), 0.f);
            if (bounds.top + bounds.height > winSize.y)
                transform->MoveBy(0.f, -(bounds.top + bounds.height - winSize.y));
        }

        // Обработка выхода из триггеров
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
        // простое разрешение коллизии
        if (intersection.width > intersection.height)
        {
            if (movingCollider->GetBounds().top < staticCollider->GetBounds().top)
                movingTransform->MoveBy(0.f, -intersection.height * moveFactor);
            else
                movingTransform->MoveBy(0.f, intersection.height * moveFactor);
        }
        else
        {
            if (movingCollider->GetBounds().left < staticCollider->GetBounds().left)
                movingTransform->MoveBy(-intersection.width * moveFactor, 0.f);
            else
                movingTransform->MoveBy(intersection.width * moveFactor, 0.f);
        }
    }
}
