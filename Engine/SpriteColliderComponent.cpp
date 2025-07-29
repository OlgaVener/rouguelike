#include "pch.h"
#include "SpriteColliderComponent.h"


GameEngine::SpriteColliderComponent::SpriteColliderComponent(GameObject* gameObject) : ColliderComponent(gameObject)
{
	auto spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
	if (spriteRenderer == nullptr)
	{
		std::cout << "SpriteRenderer required to SpriteCollider." << std::endl;
		gameObject->RemoveComponent(this);
		return;
	}
}

GameEngine::SpriteColliderComponent::~SpriteColliderComponent()
{
}

void GameEngine::SpriteColliderComponent::Update(float deltaTime)
{
}

void GameEngine::SpriteColliderComponent::Render()
{
}
