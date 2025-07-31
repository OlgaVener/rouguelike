#pragma once
#include "pch.h"
#include "PhysicsSystem.h"

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
            auto body = colliders[i]->GetGameObject()->GetComponent<RigidbodyComponent>();
            if (body && body->GetKinematic())
            {
                continue;
            }

            for (size_t j = 0; j < colliders.size(); ++j)
            {
                if (j == i)
                    continue;

                sf::FloatRect intersection;
                if (colliders[i]->GetBounds().intersects(colliders[j]->GetBounds(), intersection))
                {
                    if (colliders[i]->IsTrigger() != colliders[j]->IsTrigger())
                    {
                        colliders[i]->InTriggerEnter(colliders[j]);
                        colliders[j]->InTriggerEnter(colliders[i]);
                    }
                }
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
}
