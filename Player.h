#pragma once

#include "CameraComponent.h"
#include "TransformComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Vector.h"

namespace RoguelikeGame
{
    class Player
    {
    public:
        Player();
        Player(const GameEngine::Vector2Df& position, GameEngine::GameObject* player); // TODO: Create implementation here

        GameEngine::GameObject* GetGameObject();
    private:
        GameEngine::GameObject* gameObject;
    };
}