#include "LevelBuilder.h"
#include "Wall.h"
#include "Floor.h"
#include "Player.h"
#include "Enemy.h"
#include "AudioEngine.h"
#include "AudioManager.h"
#include "GameWorld.h"
#include "ResourceSystem.h"
#include <Logger.h>

using namespace RoguelikeGame;
using namespace GameEngine;

LevelBuilder::~LevelBuilder() = default;

void LevelBuilder::Start()
{
    const float tileSize = 64.f;
    int width = 20;
    int height = 11;

    float startX = 0;
    float startY = 0;

    // === 1. Пол ===
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Vector2Df position(
                startX + x * tileSize + tileSize / 2,
                startY + y * tileSize + tileSize / 2
            );
            floors.push_back(std::make_unique<Floor>(position, 0));
        }
    }

    // === 2. Верхняя и нижняя линии (без углов) ===
    for (int x = 1; x < width - 1; ++x) {
        // верх
        walls.push_back(std::make_unique<Wall>(
            Vector2Df(startX + x * tileSize + tileSize / 2, startY + 0 * tileSize + tileSize / 2),
            0 // top
        ));
        // низ
        walls.push_back(std::make_unique<Wall>(
            Vector2Df(startX + x * tileSize + tileSize / 2, startY + (height - 1) * tileSize + tileSize / 2),
            1 // bottom
        ));
    }

    // === 3. Левая и правая линии (без углов) ===
    for (int y = 1; y < height - 1; ++y) {
        // левая
        walls.push_back(std::make_unique<Wall>(
            Vector2Df(startX + 0 * tileSize + tileSize / 2, startY + y * tileSize + tileSize / 2),
            2 // left
        ));
        // правая
        walls.push_back(std::make_unique<Wall>(
            Vector2Df(startX + (width - 1) * tileSize + tileSize / 2, startY + y * tileSize + tileSize / 2),
            3 // right
        ));
    }

    // === 4. Углы ===
    // создаём после всех стен, чтобы они были сверху
    walls.push_back(std::make_unique<Wall>(
        Vector2Df(startX + 0 * tileSize + tileSize / 2, startY + 0 * tileSize + tileSize / 2),
        4 // top-left
    ));
    walls.push_back(std::make_unique<Wall>(
        Vector2Df(startX + (width - 1) * tileSize + tileSize / 2, startY + 0 * tileSize + tileSize / 2),
        5 // top-right
    ));
    walls.push_back(std::make_unique<Wall>(
        Vector2Df(startX + 0 * tileSize + tileSize / 2, startY + (height - 1) * tileSize + tileSize / 2),
        6 // bottom-left
    ));
    walls.push_back(std::make_unique<Wall>(
        Vector2Df(startX + (width - 1) * tileSize + tileSize / 2, startY + (height - 1) * tileSize + tileSize / 2),
        7 // bottom-right
    ));

    // === 5. Игрок в центре комнаты ===
    player = std::make_shared<RoguelikeGame::Player>();
    auto playerTransform = player->GetGameObject()->GetComponent<TransformComponent>();
    playerTransform->SetWorldPosition(Vector2Df(
        startX + (width * tileSize) / 2,
        startY + (height * tileSize) / 2
    ));

    // === 6. Враг ===
    ai = std::make_shared<RoguelikeGame::EnemyAI>(
        Vector2Df(startX + tileSize * 2, startY + tileSize * 2),
        player->GetGameObject()
    );

    // === 7. Аудио ===
    audio = std::make_unique<AudioEngine>(player->GetGameObject());
    InitializeAudio();
}

void LevelBuilder::InitializeAudio()
{
    // Загружаем звуки в ресурсную систему
    GameEngine::ResourceSystem::Instance()->LoadAllSounds();

    // Инициализируем аудио менеджер
    AudioManager::Instance().Initialize();

    // Запускаем фоновую музыку
    AudioManager::Instance().PlayBackgroundMusic();

    std::cout << "Audio system initialized" << std::endl;
}

void LevelBuilder::Restart()
{
    Stop();
    Start();
}

void LevelBuilder::Stop()
{
    AudioManager::Instance().StopAllSounds();
    GameWorld::Instance()->Clear();
}
