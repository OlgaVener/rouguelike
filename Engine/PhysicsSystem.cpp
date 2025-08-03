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

            for (int j = 0; j < colliders.size(); ++j)
            {
                if (j == i)
                {
                    continue;
                }

                sf::FloatRect intersection;
                if (colliders[i]->GetBounds().intersects(colliders[j]->GetBounds(), intersection))
                {
                    if (colliders[i]->IsTrigger() != colliders[j]->IsTrigger())
                    {
                        auto trigger = new Trigger(colliders[i], colliders[j]);
                        colliders[i]->OnTriggerEnter(colliders[j]);
                        colliders[j]->OnTriggerEnter(colliders[i]);

                        triggersEnteredPair.emplace(colliders[i], colliders[j]);
                    }
                }
                else if (!colliders[i]->IsTrigger())
                {
                    float intersectionWidth = intersection.width;
                    float intersectionHeight = intersection.height;
                    Vector2Df intersectionPosition = { intersection.left = 0.5f * intersectionWidth, intersection.top - 0.5f * intersectionHeight };

                    Vector2Df aPosition = { colliders[i]->GetBounds().left, colliders[i]->GetBounds().top };
                    auto aTransform = colliders[i]->GetGameObject()->GetComponent<TransformComponent>();

                    if (intersectionWidth > intersectionHeight)
                    {
                        if (intersectionPosition.y > aPosition.y)
                        {
                            aTransform->MoveBy({ 0, -intersectionHeight });
                            std::cout << "Top collision" << std::endl;
                        }
                        else
                        {
                            aTransform->MoveBy({ 0, intersectionHeight });
                            std::cout << "Down collision" << std::endl;
                        }
                    }
                    else
                    {
                        if (intersectionPosition.x > aPosition.x)
                        {
                            aTransform->MoveBy({ -intersectionWidth, 0.f });
                            std::cout << "Right collision" << std::endl;
                        }
                        else
                        {
                            aTransform->MoveBy({ -intersectionWidth, 0.f });
                            std::cout << "Left collision" << std::endl;
                        }
                    }

                    auto collision = new Collision(colliders[i], colliders[j], intersection);
                    colliders[i]->OnCollision(colliders[j]);
                    colliders[j]->OnCollision(colliders[i]);
                }
            }
        }

        for (auto triggeredPair = triggersEnteredPair.cbegin(), nextTriggeredPair = triggeredPair; triggeredPair != triggersEnteredPair.cend(); triggeredPair = nextTriggeredPair)
        {
            ++nextTriggeredPair;
            if (!triggeredPair->first->GetBounds().intersects(triggeredPair->second->GetBounds()))
            {
                auto trigger = new Trigger(triggeredPair->first, triggeredPair->second);
                triggeredPair->first->OnTriggerExit(*trigger);
                triggeredPair->second->OnTriggerExit(*trigger);

                triggersEnteredPair.erase(triggeredPair);
            }
        }
    }

    void PhysicsSystem::Subscribe(ColliderComponent* collider)
    {
        std::cout << "Subscribe " << collider << std::endl;
        colliders.push_back(collider);
    }

    void PhysicsSystem::Unsubscribe(ColliderComponent* collider)
    {
        std::cout << "Unsubscribe " << collider << std::endl;
        colliders.erase(std::remove(colliders.begin(), colliders.end(), collider), colliders.end());
    }
}
