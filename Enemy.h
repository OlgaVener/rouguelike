#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Vector.h"
#include <CameraComponent.h>

namespace RoguelikeGame
{
	class EnemyAI
	{
	public:
		EnemyAI(const GameEngine::Vector2Df& position, GameEngine::GameObject* player);
		GameEngine::GameObject* GetGameObject();
	private:
		GameEngine::GameObject* gameObject;
	};
}
