#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

namespace GameEngine
{
    class AudioEngine {
    public:
        AudioEngine() = default;
        ~AudioEngine() = default;

        // Загружает музыку по ID
        bool loadMusic(const std::string& id, const std::string& filepath);

        // Воспроизводит музыку с указанным ID
        void playMusic(const std::string& id, bool loop = true);

        // Останавливает музыку
        void stopMusic(const std::string& id);

    private:
        std::unordered_map<std::string, std::unique_ptr<sf::Music>> musicMap;
    };
}