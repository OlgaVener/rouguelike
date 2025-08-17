#include "Enemy.h"
#include "FollowComponent.h"
#include <SpriteColliderComponent.h>

namespace RoguelikeGame 
{
	EnemyAI::EnemyAI(const GameEngine::Vector2Df& position, GameEngine::GameObject* player)
	{
		//Устанавливается игровой объект с позицией
		gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("AI");
		auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		//Загрузка текстуры и её размеры
		auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
		renderer->SetTexture(GameEngine::ResourceSystem::Instance()->GetTextureMapElementShared("AI", 0));
		renderer->SetPixelSize(100, 100);

		//Преследование игрока и скорость
		auto follower = gameObject->AddComponent<GameEngine::FollowComponent>();
		follower->SetTarget(player);
		follower->SetSpeed(120.f);

		//Физика
		auto rigidbody = gameObject->AddComponent<GameEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		//Обнаружение столкновений
		auto collider = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();
	}

	GameEngine::GameObject* EnemyAI::GetGameObject()
	{
		return gameObject;
	}


}