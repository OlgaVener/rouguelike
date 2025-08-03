#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

namespace GameEngine
{
    class AudioEngine {
    public:
        AudioEngine() = default;
        ~AudioEngine() = default;

        // ��������� ������ �� ID
        bool loadMusic(const std::string& id, const std::string& filepath);

        // ������������� ������ � ��������� ID
        void playMusic(const std::string& id, bool loop = true);

        // ������������� ������
        void stopMusic(const std::string& id);

    private:
        std::unordered_map<std::string, std::unique_ptr<sf::Music>> musicMap;
    };
}