#include "LevelBuilder.h"
#include "Floor.h"
#include "AudioEngine.h"
#include "Enemy.h"
#include "Player.h"

using namespace GameEngine;

LevelBuilder::~LevelBuilder() = default;

void LevelBuilder::Start()
{
    int width = 15;
    int height = 15;

    // Создаём игрока
    player = std::make_shared<RoguelikeGame::Player>();

    // Создаём ИИ врага
    ai = std::make_shared<RoguelikeGame::EnemyAI>(
        Vector2Df(width / 3 * 128.f, height / 3 * 128.f),
        player->GetGameObject()
    );

    // Создаём аудио
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
