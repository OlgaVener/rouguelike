#include "pch.h"
#include "ResourceSystem.h"
#include <iostream>

namespace GameEngine
{
    ResourceSystem* ResourceSystem::Instance()
    {
        static ResourceSystem instance;
        return &instance;
    }

    void ResourceSystem::LoadTexture(const std::string& name, const std::string& sourcePath, bool isSmooth)
    {
        auto texture = new sf::Texture();
        if (!texture->loadFromFile(sourcePath))
        {
            std::cerr << "No texture " << sourcePath << std::endl;
            delete texture;
            return;
        }
        texture->setSmooth(isSmooth);
        textures[name] = texture;
    }

    const sf::Texture* ResourceSystem::GetTextureShared(const std::string& name) const
    {
        auto it = textures.find(name);
        return it != textures.end() ? it->second : nullptr;
    }

    void ResourceSystem::LoadTextureMap(const std::string& name, const std::string& sourcePath,
        sf::Vector2u elementPixelSize, int totalElements, bool isSmooth)
    {
        sf::Texture bigTexture;
        if (!bigTexture.loadFromFile(sourcePath))
        {
            std::cerr << "Textures not loaded: " << sourcePath << std::endl;
            return;
        }
        bigTexture.setSmooth(isSmooth);

        std::vector<sf::Texture*> elements;
        for (int i = 0; i < totalElements; ++i)
        {
            auto tex = new sf::Texture();
            tex->loadFromImage(
                bigTexture.copyToImage(),
                sf::IntRect(i * elementPixelSize.x, 0, elementPixelSize.x, elementPixelSize.y)
            );
            tex->setSmooth(isSmooth);
            elements.push_back(tex);
        }
        textureMaps[name] = elements;
    }

    sf::Texture* ResourceSystem::GetTextureCopy(const std::string& name) const
    {
        auto it = textures.find(name);
        if (it != textures.end())
            return new sf::Texture(*it->second);
        return nullptr;
    }

    void ResourceSystem::DeleteSharedTexture(const std::string& name)
    {
        auto it = textures.find(name);
        if (it != textures.end())
        {
            delete it->second;
            textures.erase(it);
        }
    }


    const sf::Texture* ResourceSystem::GetTextureMapElementShared(const std::string& name, int elementIndex) const
    {
        auto it = textureMaps.find(name);
        if (it != textureMaps.end() && elementIndex >= 0 && elementIndex < (int)it->second.size())
            return it->second[elementIndex];
        return nullptr;
    }

    sf::Texture* ResourceSystem::GetTextureMapElementCopy(const std::string& name, int elementIndex) const
    {
        auto it = textureMaps.find(name);
        if (it != textureMaps.end() && elementIndex >= 0 && elementIndex < (int)it->second.size())
            return new sf::Texture(*it->second[elementIndex]);
        return nullptr;
    }

    int ResourceSystem::GetTextureMapElementsCount(const std::string& name) const
    {
        auto it = textureMaps.find(name);
        return (it != textureMaps.end()) ? (int)it->second.size() : 0;
    }

    void ResourceSystem::DeleteSharedTextureMap(const std::string& name)
    {
        auto it = textureMaps.find(name);
        if (it != textureMaps.end())
        {
            for (auto tex : it->second) delete tex;
            textureMaps.erase(it);
        }
    }

    void ResourceSystem::LoadSoundBuffer(const std::string& name, const std::string& sourcePath)
    {
        auto buffer = new sf::SoundBuffer();
        if (!buffer->loadFromFile(sourcePath))
        {
            std::cerr << "No sound " << sourcePath << std::endl;
            delete buffer;
            return;
        }
        soundBuffers[name] = buffer;
    }

    const sf::SoundBuffer* ResourceSystem::GetSoundBuffer(const std::string& name) const
    {
        auto it = soundBuffers.find(name);
        return it != soundBuffers.end() ? it->second : nullptr;
    }

    void ResourceSystem::LoadMusic(const std::string& name, const std::string& sourcePath)
    {
        auto music = new sf::Music();
        if (!music->openFromFile(sourcePath))
        {
            std::cerr << "Sound not loaded: " << sourcePath << std::endl;
            delete music;
            return;
        }
        musics[name] = music;
    }

    sf::Music* ResourceSystem::GetMusic(const std::string& name) const
    {
        auto it = musics.find(name);
        return it != musics.end() ? it->second : nullptr;
    }

    void ResourceSystem::DeleteAllTextures()
    {
        for (auto& t : textures) delete t.second;
        textures.clear();
    }

    void ResourceSystem::DeleteAllTextureMaps()
    {
        for (auto& tm : textureMaps)
            for (auto tex : tm.second) delete tex;
        textureMaps.clear();
    }

    void ResourceSystem::DeleteAllSounds()
    {
        for (auto& s : soundBuffers) delete s.second;
        soundBuffers.clear();
    }

    void ResourceSystem::DeleteAllMusic()
    {
        for (auto& m : musics) delete m.second;
        musics.clear();
    }

    void ResourceSystem::Clear()
    {
        DeleteAllTextures();
        DeleteAllTextureMaps();
        DeleteAllSounds();
        DeleteAllMusic();
    }
}
