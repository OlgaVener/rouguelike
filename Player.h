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
		Engine::GameObject* GetGameObject();
	private:
		Engine::GameObject* gameObject;
	};
}