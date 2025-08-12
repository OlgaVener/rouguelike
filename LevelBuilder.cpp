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

    for (int y = 0; y < height + 1; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            //Если просто пространство
            if (x != 0 && x != width && y != 0 && y != height)
            {
                floors.push_back(std::make_unique<Floor>(std::forward<GameEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(0)));
            }

            //Если левый нижний угол
            if (x == 0 && y == 0)
            {
                walls.push_back(std::make_unique<Wall>(std::forward<GameEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(25)));
            }

            //Если правый нижний угол
            if (x == 0 && y == 0)
            {
                walls.push_back(std::make_unique<Wall>(std::forward<GameEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(27)));
            }

            //Если левый верхний угол
            if (x == 0 && y == 0)
            {
                walls.push_back(std::make_unique<Wall>(std::forward<GameEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(1)));
            }

            //Если правый верхний угол
            if (x == 0 && y == 0)
            {
                walls.push_back(std::make_unique<Wall>(std::forward<GameEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(3)));
            }

            //Если лево
            if (x == 0 && y != height && y != 0)
            {
                floors.push_back(std::make_unique<Floor>(std::forward<GameEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(18)));
                walls.push_back(std::make_unique<Wall>(std::forward<GameEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(12)));
            }

            //Если право
            if (x == width && y != height && y != 0)
            {
                floors.push_back(std::make_unique<Floor>(std::forward<GameEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(19)));
                walls.push_back(std::make_unique<Wall>(std::forward<GameEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(12)));
            }

            //Если низ
            if (x == width && y != height && y != 0)
            {
                walls.push_back(std::make_unique<Wall>(std::forward<GameEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(38)));
            }

            //Если верх
            if (x == width && y != height && y != 0)
            {
                walls.push_back(std::make_unique<Wall>(std::forward<GameEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(38)));
            }
        }
    }

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
