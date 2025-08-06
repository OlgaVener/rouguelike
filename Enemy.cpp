#include "Enemy.h"
#include "FollowComponent.h"

namespace RoguelikeGame 
{
	RoguelikeGame::EnemyAI::EnemyAI(const GameEngine::Vector2Df& position, GameEngine::GameObject* player)
	{
		gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("AI");
		auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
		renderer->SetTexture(*GameEngine::ResourceSystem::Instance()->GetTextureMapElementShared("AI", 0));
		renderer->SetPixelSize(100, 100);

		auto follower = gameObject->AddComponent<GameEngine::FollowComponent>();
		follower->SetTarget(player);
		follower->SetSpeed(120.f);

		auto rigidbody = gameObject->AddComponent<GameEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		auto collider = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();
	}

	GameEngine::GameObject* RoguelikeGame::EnemyAI::GetGameObject()
	{
		return gameObject;
	}


}