#pragma once

#include <array>
#include <memory>
#include <vector>
#include "Scene.h"
#include "Wall.h"
#include "Floor.h"
#include "Player.h"
#include "Enemy.h"

namespace GameEngine
{
    class AudioEngine;
    //class Wall;
    //class Floor;
    
    class LevelBuilder : public Scene
    {
    public:
        ~LevelBuilder(); // Реализация будет в .cpp
        void Start() override;
        void Restart() override;
        void Stop() override;

    private:
        std::shared_ptr<RoguelikeGame::Player> player;
        std::shared_ptr<RoguelikeGame::EnemyAI> ai;
        std::unique_ptr<AudioEngine> audio;
        //std::vector<std::unique_ptr<Wall>> walls;
        //std::vector<std::unique_ptr<Floor>> floor;
    };
}