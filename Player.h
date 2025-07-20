#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"

namespace RoguelikeGame
{
	class Player
	{
	public:
		Player();
		GameEngine::GameObject* GetGameObject();
	private:
		GameEngine::GameObject* gameObject;
	};
}