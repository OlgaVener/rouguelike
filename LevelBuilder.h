#pragma once
#include <memory>
#include <vector>

#include "Floor.h"
#include "Wall.h"
#include "AudioEngine.h"
#include "Player.h"
#include "Enemy.h"

namespace GameEngine
{
    class LevelBuilder
    {
    public:
        ~LevelBuilder();

        void Start();
        void InitializeAudio();
        void Restart();
        void Stop();

    private:
        // Вектор объектов пола
        std::vector<std::unique_ptr<RoguelikeGame::Floor>> floors;

        // Вектор объектов стен
        std::vector<std::unique_ptr<RoguelikeGame::Wall>> walls;

        // Аудиосистема
        std::unique_ptr<AudioEngine> audio;

        // Игрок и враг (в shared_ptr, чтобы делить владение)
        std::shared_ptr<RoguelikeGame::Player> player;
        std::shared_ptr<RoguelikeGame::EnemyAI> ai;
    };
}
