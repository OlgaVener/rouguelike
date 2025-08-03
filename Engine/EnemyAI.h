#pragma once

#include "IPositionProvider.h"
#include <SFML/System.hpp>

namespace GameEngine {
    class EnemyAI {
    public:
        void update(IPositionProvider& enemy, const IPositionProvider& target, float detectionRadius, float speed, float dt);
    };
}
