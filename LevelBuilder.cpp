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
    //Размеры уровня
    int width = 20;
    int height = 15;
    const int topBottomWallTexture = 38;
    const int sideWallTexture = 12;
    const float tileSize = 128.f;

    // === 1. Заполняем пол ===
    float startX = (1280 - width * tileSize) / 2; // Центрирование по горизонтали
    float startY = (720 - height * tileSize) / 2; // Центрирование по вертикали

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Рассчитываем позицию с учётом центрирования
            Vector2Df position(
                startX + x * tileSize + tileSize / 2, // +tileSize/2 для центрирования
                startY + y * tileSize + tileSize / 2
            );

            floors.push_back(std::make_unique<Floor>(position, 0));
        }
    }

    // === 2. Периметр стен ===
         // Верхние и нижние стены
    for (int x = 0; x < width; ++x) {
        // Верхняя стена
        walls.push_back(std::make_unique<Wall>(
            Vector2Df(startX + x * tileSize + tileSize / 2, startY - tileSize / 2),
            topBottomWallTexture
        ));

        // Нижняя стена
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
