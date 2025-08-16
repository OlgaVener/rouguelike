#include "LevelBuilder.h"
#include "Wall.h"
#include "Floor.h"
#include "Player.h"
#include "Enemy.h"
#include "AudioEngine.h"
#include "GameWorld.h"
#include "ResourceSystem.h"

using namespace RoguelikeGame;
using namespace GameEngine;

LevelBuilder::~LevelBuilder() = default;

void LevelBuilder::Start()
{
    auto res = ResourceSystem::Instance();

    // Загружаем тайлсеты (один раз)
    if (!res->GetTextureMapElementShared("walls.png", 0))
    {
        res->LoadTextureMap("walls.png", "assets/walls.png", { 128, 128 }, 40, true);
    }
    if (!res->GetTextureMapElementShared("floor.png", 0))
    {
        res->LoadTextureMap("floor.png", "assets/floor.png", { 128, 128 }, 20, true);
    }

    int width = 15;
    int height = 15;

    // === 1. Заполняем пол ===
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            floors.push_back(std::make_unique<Floor>(Vector2Df(x * 128.f, y * 128.f), 0));
        }
    }

    // === 2. Периметр стен ===
    for (int x = 0; x < width; ++x)
    {
        walls.push_back(std::make_unique<Wall>(Vector2Df(x * 128.f, 0.f), 38));                // верх
        walls.push_back(std::make_unique<Wall>(Vector2Df(x * 128.f, (height - 1) * 128.f), 38)); // низ
    }
    for (int y = 0; y < height; ++y)
    {
        walls.push_back(std::make_unique<Wall>(Vector2Df(0.f, y * 128.f), 12));                 // слева
        walls.push_back(std::make_unique<Wall>(Vector2Df((width - 1) * 128.f, y * 128.f), 12)); // справа
    }

    // === 3. Игрок ===
    player = std::make_shared<RoguelikeGame::Player>();

    // === 4. Враг ===
    ai = std::make_shared<RoguelikeGame::EnemyAI>(
        Vector2Df(width / 3.f * 128.f, height / 3.f * 128.f),
        player->GetGameObject()
    );

    // === 5. Аудио ===
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
