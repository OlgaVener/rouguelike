#include <array>
#include <memory>
#include <vector>
#include "Scene.h"
#include "Music.h"
#include "Floor.h"
#include "Wall.h"
#include "Player.h"
#include "Enemy.h"

namespace GameEngine
{
    class Player;
    class Music;
    class Wall;
    class Floor;

    class LevelBuilder : public Scene
    {
    public:
        void Start() override;
        void Restart() override;
        void Stop() override;
    private:
        std::shared_ptr<Player> player;
        std::shared_ptr<RoguelikeGame::EnemyAI> ai;
        std::unique_ptr<Music> music;
        std::vector<std::unique_ptr<Wall>> walls;
        std::vector<std::unique_ptr<Floor>> floor;
    };
}
