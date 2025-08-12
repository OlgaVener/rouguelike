#include "LevelBuilder.h"
#include "Wall.h"       
#include "AudioEngine.h"
#include "GameWorld.h"
#include "Floor.h"
#include "Player.h"
#include "Enemy.h"
#include "ResourceSystem.h"

using namespace RoguelikeGame;
using namespace GameEngine;

// Деструктор по умолчанию (unique_ptr сами освободят память)
LevelBuilder::~LevelBuilder() = default;

void LevelBuilder::Start()
{
    int width = 15;   // ширина уровня
    int height = 15;  // высота уровня

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Пол
            if (x != 0 && x != width && y != 0 && y != height)
            {
                floors.push_back(std::make_unique<Floor>(
                    Vector2Df(x * 128.f, y * 128.f), 0));
            }

            // Углы
            if (x == 0 && y == 0)
                walls.push_back(std::make_unique<Wall>(Vector2Df(x * 128.f, y * 128.f), 25));

            if (x == width && y == 0)
                walls.push_back(std::make_unique<Wall>(Vector2Df(x * 128.f, y * 128.f), 27));

            if (x == 0 && y == height)
                walls.push_back(std::make_unique<Wall>(Vector2Df(x * 128.f, y * 128.f), 1));

            if (x == width && y == height)
                walls.push_back(std::make_unique<Wall>(Vector2Df(x * 128.f, y * 128.f), 3));

            // Левая граница
            if (x == 0 && y != height && y != 0)
            {
                floors.push_back(std::make_unique<Floor>(Vector2Df(x * 128.f, y * 128.f), 18));
                walls.push_back(std::make_unique<Wall>(Vector2Df(x * 128.f, y * 128.f), 12));
            }

            // Правая граница
            if (x == width && y != height && y != 0)
            {
                floors.push_back(std::make_unique<Floor>(Vector2Df(x * 128.f, y * 128.f), 19));
                walls.push_back(std::make_unique<Wall>(Vector2Df(x * 128.f, y * 128.f), 12));
            }

            // Верхняя граница
            if (y == 0 && x != 0 && x != width)
                walls.push_back(std::make_unique<Wall>(Vector2Df(x * 128.f, y * 128.f), 38));

            // Нижняя граница
            if (y == height && x != 0 && x != width)
                walls.push_back(std::make_unique<Wall>(Vector2Df(x * 128.f, y * 128.f), 38));
        }
    }

    // Игрок
    player = std::make_shared<RoguelikeGame::Player>();

    // Враг
    ai = std::make_shared<RoguelikeGame::EnemyAI>(
        Vector2Df(width / 3.f * 128.f, height / 3.f * 128.f),
        player->GetGameObject()
    );

    // Аудио
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
