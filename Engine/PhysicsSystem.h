#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "Trigger.h"
#include <RigidbodyComponent.h>

namespace GameEngine
{
    class PhysicsSystem
    {
    public:
        static PhysicsSystem* Instance();

        void Update();
        void Subscribe(ColliderComponent* collider);
        void Unsubscribe(ColliderComponent* collider);

        float GetFixedDeltaTime() const;

        void ResolveCollision(TransformComponent* movingTransform,
            ColliderComponent* movingCollider,
            ColliderComponent* staticCollider,
            const sf::FloatRect& intersection,
            float moveFactor);
        void MoveWithCollision(RigidbodyComponent* rb, Vector2Df desiredMove);

    private:
        PhysicsSystem() = default;

        std::vector<ColliderComponent*> colliders;
        std::vector<std::pair<ColliderComponent*, ColliderComponent*>> triggersEnteredPair;
        float fixedDeltaTime = 0.016f;
        // 60 fps
    };
}
