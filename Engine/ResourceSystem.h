#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace GameEngine
{
    class ResourceSystem
    {
    public:
        static ResourceSystem* Instance();

        // --- Текстуры ---
        void LoadTexture(const std::string& name, const std::string& sourcePath, bool isSmooth = false);
        const sf::Texture* GetTextureShared(const std::string& name) const;
        sf::Texture* GetTextureCopy(const std::string& name) const;
        void DeleteSharedTexture(const std::string& name);

        // --- Атласы ---
        void LoadTextureMap(const std::string& name, const std::string& sourcePath,
            sf::Vector2u elementPixelSize, int totalElements, bool isSmooth = false);
        const sf::Texture* GetTextureMapElementShared(const std::string& name, int elementIndex) const;
        sf::Texture* GetTextureMapElementCopy(const std::string& name, int elementIndex) const;
        int GetTextureMapElementsCount(const std::string& name) const;
        void DeleteSharedTextureMap(const std::string& name);

        // --- Звуки ---
        void LoadSoundBuffer(const std::string& name, const std::string& sourcePath);
        const sf::SoundBuffer* GetSoundBuffer(const std::string& name) const;

        // --- Музыка ---
        void LoadMusic(const std::string& name, const std::string& sourcePath);
        sf::Music* GetMusic(const std::string& name) const;

        // --- Очистка ---
        void DeleteAllTextures();
        void DeleteAllTextureMaps();
        void DeleteAllSounds();
        void DeleteAllMusic();
        void Clear();

    private:
        ResourceSystem() = default;
        ~ResourceSystem() { Clear(); }

        std::unordered_map<std::string, sf::Texture*> textures;
        std::unordered_map<std::string, std::vector<sf::Texture*>> textureMaps;
        std::unordered_map<std::string, sf::SoundBuffer*> soundBuffers;
        std::unordered_map<std::string, sf::Music*> musics;
    };
}
