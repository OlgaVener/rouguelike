#include "Enemy.h"
#include "FollowComponent.h"
#include <SpriteColliderComponent.h>

namespace RoguelikeGame 
{
	EnemyAI::EnemyAI(const GameEngine::Vector2Df& position, GameEngine::GameObject* player)
	{
		//��������������� ������� ������ � ��������
        gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("AI");
        auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
        transform->SetWorldPosition(position);

        // ������� �������� ��� �����
        sf::Texture* texture = new sf::Texture();
        if (texture->create(100, 100)) {
            sf::Image image;
            image.create(100, 100, sf::Color::Yellow); // ������ ���

            // ������� ���� ��� �����
            for (int i = 0; i < 100; i++) {
                image.setPixel(i, 50, sf::Color::Red);    // ����������� �����
                image.setPixel(50, i, sf::Color::Green);  // ������������ �����
            }

            texture->loadFromImage(image);
        }

        auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
        renderer->SetTexture(texture);
        renderer->SetPixelSize(100, 100);

		//������������� ������ � ��������
		auto follower = gameObject->AddComponent<GameEngine::FollowComponent>();
		follower->SetTarget(player);
		follower->SetSpeed(120.f);

		//������
		auto rigidbody = gameObject->AddComponent<GameEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		//����������� ������������
		auto collider = gameObject->AddComponent<GameEngine::SpriteColliderComponent>();
	}

	GameEngine::GameObject* EnemyAI::GetGameObject()
	{
		return gameObject;
	}


}