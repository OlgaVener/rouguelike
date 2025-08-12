#pragma once

#include <GameWorld.h>
#include <SpriteRendererComponent.h>
#include <ResourceSystem.h>
#include "GameObject.h"

namespace RoguelikeGame
{
    class Floor
    {
    public:
        Floor(const GameEngine::Vector2D<float>& position, int textureMapIndex);
    private:
        GameEngine::GameObject* gameObject;
    };
}