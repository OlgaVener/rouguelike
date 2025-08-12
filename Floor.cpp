#include "Floor.h"

RoguelikeGame::Floor::Floor(const GameEngine::Vector2D<float>& position, int textureMapIndex)
    : gameObject(nullptr)
{
    // ������� ������� ������
    gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("Floor");

    // ������������� �������
    auto transform = gameObject->GetComponent<GameEngine::TransformComponent>();
    transform->SetWorldPosition(position);

    // �������� �������� �� ������ �� �������
    const sf::Texture* texture = GameEngine::ResourceSystem::Instance()
        ->GetTextureMapElementShared("level_floors", textureMapIndex);

    // ��������� ��������� ��������� � ����������� ���
    auto renderer = gameObject->AddComponent<GameEngine::SpriteRendererComponent>();
    renderer->SetTexture(*texture);
    renderer->SetPixelSize(128, 128);
}