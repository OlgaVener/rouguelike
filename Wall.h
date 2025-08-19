#pragma once

#include <GameWorld.h>
#include <ResourceSystem.h>
#include "GameObject.h"
#include <FollowComponent.h>
#include <SpriteColliderComponent.h>

namespace RoguelikeGame
{
	class Wall
	{
	public:
		Wall(const GameEngine::Vector2Df position, int textureMapIndex);
		GameEngine::GameObject* GetGameObject() const { return gameObject; }
	private:
		GameEngine::GameObject* gameObject;
	};
}
