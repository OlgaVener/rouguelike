#include <vector>
#include <memory>
#include "Tile.h"

namespace GameEngine
{
    class LevelBuilder {
    public:
        // ������ ����� �� ���������
        void generateBorder(std::vector<std::vector<std::shared_ptr<Tile>>>& grid, int width, int height);

        // ��������� ��������� ������� �����
        void fillFloor(std::vector<std::vector<std::shared_ptr<Tile>>>& grid, int width, int height);
    };
}
