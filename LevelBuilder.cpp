#include "LevelBuilder.h"
#include "Wall.h"
#include "Floor.h"
#include "Player.h"
#include "Enemy.h"
#include "AudioEngine.h"
#include "GameWorld.h"
#include "ResourceSystem.h"
#include <Logger.h>

using namespace RoguelikeGame;
using namespace GameEngine;

LevelBuilder::~LevelBuilder() = default;

void LevelBuilder::Start()
{
    const float tileSize = 64.f;
    int width = 20;    // 20 * 64 = 1280 (ровно по ширине)
    int height = 11;   // 11 * 64 = 704 (больше 720, но уберем отступы)

    // УБИРАЕМ отступы полностью - начинаем с самого верха!
    float startX = 0;
    float startY = 0;  // Начинаем с самого верха, нижняя часть будет обрезана

    const int topBottomWallTexture = 38;
    const int sideWallTexture = 12;

    // === 1. Заполняем пол ===
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Vector2Df position(
                startX + x * tileSize + tileSize / 2,
                startY + y * tileSize + tileSize / 2
            );
            floors.push_back(std::make_unique<Floor>(position, 0));
        }
    }

    // === 2. Периметр стен ===
    // Верхние стены
    for (int x = 0; x < width; ++x) {
        walls.push_back(std::make_unique<Wall>(
            Vector2Df(startX + x * tileSize + tileSize / 2, startY + tileSize / 2),
            topBottomWallTexture
        ));
    }

    // Нижние стены  
    for (int x = 0; x < width; ++x) {
        walls.push_back(std::make_unique<Wall>(
            Vector2Df(startX + x * tileSize + tileSize / 2, startY + (height - 1) * tileSize + tileSize / 2),
            topBottomWallTexture
        ));
    }

    // Боковые стены
    for (int y = 1; y < height - 1; ++y) {
        // Левая стена
        walls.push_back(std::make_unique<Wall>(
            Vector2Df(startX + tileSize / 2, startY + y * tileSize + tileSize / 2),
            sideWallTexture
        ));

        // Правая стена
        walls.push_back(std::make_unique<Wall>(
            Vector2Df(startX + (width - 1) * tileSize + tileSize / 2, startY + y * tileSize + tileSize / 2),
            sideWallTexture
        ));
    }

    // === 3. Игрок в центре комнаты ===
    player = std::make_shared<RoguelikeGame::Player>();
    auto playerTransform = player->GetGameObject()->GetComponent<TransformComponent>();

    float playerX = startX + (width * tileSize) / 2;
    float playerY = startY + (height * tileSize) / 2;

    playerTransform->SetWorldPosition(Vector2Df(playerX, playerY));

    // === 4. Враг ===
    ai = std::make_shared<RoguelikeGame::EnemyAI>(
        Vector2Df(startX + tileSize * 2, startY + tileSize * 2),
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
