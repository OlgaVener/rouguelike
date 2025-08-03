#include <vector>
#include <memory>
#include "Tile.h"

namespace GameEngine
{
    class LevelBuilder {
    public:
        // Строит стены по периметру
        void generateBorder(std::vector<std::vector<std::shared_ptr<Tile>>>& grid, int width, int height);

        // Заполняет остальную область полом
        void fillFloor(std::vector<std::vector<std::shared_ptr<Tile>>>& grid, int width, int height);
    };
}
