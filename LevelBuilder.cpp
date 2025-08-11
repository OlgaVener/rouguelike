#include "LevelBuilder.h"
#include "AudioEngine.h"
#include "Enemy.h"
#include "Player.h"

using namespace GameEngine;

LevelBuilder::~LevelBuilder() = default;

void LevelBuilder::Start()
{
    int width = 15;
    int height = 15;

    // ������ ������
    player = std::make_unique<RoguelikeGame::Player>(Vector2Df(width / 2 * 128.f, height / 2 * 128.f)
    );

    // ������ �����
    ai = std::make_unique<RoguelikeGame::EnemyAI>(
        Vector2Df(width / 3 * 128.f, height / 3 * 128.f),
        player->GetGameObject()
    );

    // ������ �������������� � ���������� ����
    audio = std::make_unique<AudioEngine>(player->GetGameObject());
}

void LevelBuilder::Restart()
{
    Stop();
    Start();
}

void LevelBuilder::Stop()
{
    GameWorld::Instance()->Clear();
}