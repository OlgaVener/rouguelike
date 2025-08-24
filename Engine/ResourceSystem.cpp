#include "pch.h"
#include "ResourceSystem.h"
#include "Logger.h"
#include <iostream>
#include <filesystem>

namespace GameEngine
{
    // Реализация singleton-паттерна
    ResourceSystem* ResourceSystem::Instance()
    {
        static ResourceSystem instance; // Единственный экземпляр
        return &instance;
    }

    // Загрузка текстуры из файла
    void ResourceSystem::LoadTexture(const std::string& name, const std::string& sourcePath, bool isSmooth) {
        // Логирование попытки загрузки текстуры
        LOG_INFO("Attempting to load texture: " + name + " from: " + sourcePath);

        // Проверка существования файла
        if (!std::filesystem::exists(sourcePath)) {
            LOG_ERROR("Texture file not found: " + sourcePath);
            return;
        }

        // Попытка загрузки изображения
        sf::Image img;
        if (!img.loadFromFile(sourcePath)) {
            LOG_ERROR("Failed to load image data from: " + sourcePath);
            return;
        }

        // Логирование информации о изображении
        LOG_INFO("Image loaded. Size: " + std::to_string(img.getSize().x) +
            "x" + std::to_string(img.getSize().y) +
            " Channels: " + std::to_string(img.getPixel(0, 0).a));

        // Создание текстуры
        auto texture = new sf::Texture();
        if (!texture->loadFromImage(img)) {
            LOG_ERROR("Failed to create texture from image. Possible reasons:");
            LOG_ERROR("- Invalid image dimensions");
            LOG_ERROR("- Unsupported pixel format");
            LOG_ERROR("- Driver/hardware limitations");
            delete texture;
            return;
        }

        // Проверка размера текстуры
        auto texSize = texture->getSize();
        if (texSize.x == 0 || texSize.y == 0) {
            LOG_ERROR("Created texture has zero size: " + std::to_string(texSize.x) +
                "x" + std::to_string(texSize.y));
            delete texture;
            return;
        }

        if (texSize.x > 32768 || texSize.y > 32768) {
            LOG_ERROR("Texture exceeds maximum size: " + std::to_string(texSize.x) +
                "x" + std::to_string(texSize.y));
            delete texture;
            return;
        }

        texture->setSmooth(isSmooth);
        textures[name] = texture;

        LOG_INFO("Texture successfully loaded: " + name +
            " Size: " + std::to_string(texSize.x) +
            "x" + std::to_string(texSize.y));
    }

    // Получение указателя на текстуру (без передачи владения)
    const sf::Texture* ResourceSystem::GetTextureShared(const std::string& name) const
    {
        auto it = textures.find(name);
        return it != textures.end() ? it->second : nullptr; // Возвращаем nullptr если не найдено
    }

    // Загрузка текстурного атласа (набора текстур из одного файла)
    void ResourceSystem::LoadTextureMap(const std::string& name, const std::string& sourcePath,
        sf::Vector2u elementPixelSize, int totalElements, bool isSmooth)
    {
        // Проверка существования файла
        if (!std::filesystem::exists(sourcePath)) {
            LOG_ERROR("Texture map file not found: " + sourcePath);
            return;
        }

        sf::Texture bigTexture;
        if (!bigTexture.loadFromFile(sourcePath))
        {
            LOG_ERROR("Failed to load texture map: " + sourcePath);
            return;
        }

        // Проверка размеров
        auto bigSize = bigTexture.getSize();
        LOG_INFO("Loading texture map: " + name + " Size: " +
            std::to_string(bigSize.x) + "x" + std::to_string(bigSize.y));

        if (elementPixelSize.x == 0 || elementPixelSize.y == 0) {
            LOG_ERROR("Invalid element size for texture map: " + name);
            return;
        }

        // Разделение большой текстуры на элементы
        std::vector<sf::Texture*> elements;
        for (int i = 0; i < totalElements; ++i)
        {
            // Проверка, не выходим ли мы за границы текстуры
            if ((i + 1) * elementPixelSize.x > bigSize.x) {
                LOG_ERROR("Texture map element " + std::to_string(i) +
                    " exceeds texture bounds in: " + name);
                break;
            }

            auto tex = new sf::Texture();
            if (!tex->loadFromImage(
                bigTexture.copyToImage(),
                sf::IntRect(i * elementPixelSize.x, 0, elementPixelSize.x, elementPixelSize.y)
            )) {
                LOG_ERROR("Failed to create texture map element " + std::to_string(i) +
                    " for: " + name);
                delete tex;
                continue;
            }
            tex->setSmooth(isSmooth);
            elements.push_back(tex);

            LOG_INFO("Created texture map element: " + name + "[" + std::to_string(i) +
                "] Size: " + std::to_string(elementPixelSize.x) +
                "x" + std::to_string(elementPixelSize.y));
        }

        textureMaps[name] = elements;
        LOG_INFO("Texture map loaded: " + name + " with " +
            std::to_string(elements.size()) + " elements");
    }

    // Создание копии текстуры (с передачей владения)
    sf::Texture* ResourceSystem::GetTextureCopy(const std::string& name) const
    {
        auto it = textures.find(name);
        if (it != textures.end())
            return new sf::Texture(*it->second); // Создаем новую копию
        return nullptr;
    }

    // Удаление текстуры из системы
    void ResourceSystem::DeleteSharedTexture(const std::string& name)
    {
        auto it = textures.find(name);
        if (it != textures.end())
        {
            delete it->second;    // Освобождение памяти
            textures.erase(it);   // Удаление из контейнера
        }
    }

    // Получение элемента из текстурного атласа (без передачи владения)
    const sf::Texture* ResourceSystem::GetTextureMapElementShared(const std::string& name, int elementIndex) const
    {
        auto it = textureMaps.find(name);
        if (it != textureMaps.end() && elementIndex >= 0 && elementIndex < (int)it->second.size())
            return it->second[elementIndex];
        return nullptr;
    }

    // Создание копии элемента из текстурного атласа (с передачей владения)
    sf::Texture* ResourceSystem::GetTextureMapElementCopy(const std::string& name, int elementIndex) const
    {
        auto it = textureMaps.find(name);
        if (it != textureMaps.end() && elementIndex >= 0 && elementIndex < (int)it->second.size())
            return new sf::Texture(*it->second[elementIndex]);
        return nullptr;
    }

    // Получение количества элементов в текстурном атласе
    int ResourceSystem::GetTextureMapElementsCount(const std::string& name) const
    {
        auto it = textureMaps.find(name);
        return (it != textureMaps.end()) ? (int)it->second.size() : 0;
    }

    // Удаление текстурного атласа
    void ResourceSystem::DeleteSharedTextureMap(const std::string& name)
    {
        auto it = textureMaps.find(name);
        if (it != textureMaps.end())
        {
            for (auto tex : it->second) delete tex; // Удаление всех текстур
            textureMaps.erase(it);                  // Удаление из контейнера
        }
    }

    // Загрузка звукового буфера
    void ResourceSystem::LoadSoundBuffer(const std::string& name, const std::string& sourcePath)
    {
        auto buffer = new sf::SoundBuffer();
        if (!buffer->loadFromFile(sourcePath))
        {
            std::cerr << "No sound " << sourcePath << std::endl;
            delete buffer;
            return;
        }
        soundBuffers[name] = buffer; // Сохранение в контейнер
    }

    // Получение звукового буфера
    const sf::SoundBuffer* ResourceSystem::GetSoundBuffer(const std::string& name) const
    {
        auto it = soundBuffers.find(name);
        return it != soundBuffers.end() ? it->second : nullptr;
    }

    // Загрузка музыки (устаревший метод)
    void ResourceSystem::LoadMusic(const std::string& name, const std::string& sourcePath) {
        auto music = std::make_unique<sf::Music>();
        if (!music->openFromFile(sourcePath)) {
            std::cerr << "Failed to load music: " << sourcePath << std::endl;
            return;
        }
        musics[name] = music.release(); // Передача владения
    }

    // Улучшенный метод загрузки музыки с кэшированием
    sf::Music* ResourceSystem::GetMusic(const std::string& filename) {
        // Проверка кэша
        if (auto it = musicCache.find(filename); it != musicCache.end()) {
            return it->second.get();
        }

        // Загрузка музыки
        auto music = std::make_unique<sf::Music>();
        std::filesystem::path fullPath = std::filesystem::current_path() / "Resources" / "Sounds" / "main_theme.wav";

        if (!music->openFromFile(fullPath.string())) {
            std::cerr << "Failed to load music: " << fullPath << std::endl;
            return nullptr;
        }

        // Сохраняем в кэш
        auto* musicPtr = music.get();
        musicCache[filename] = std::move(music);
        return musicPtr;
    }

    // Методы очистки ресурсов
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

    void ResourceSystem::DeleteAllMusic() {
        for (auto& m : musics) delete m.second;
        musics.clear();
        musicCache.clear();
    }

    // Полная очистка всех ресурсов
    void ResourceSystem::Clear()
    {
        DeleteAllTextures();
        DeleteAllTextureMaps();
        DeleteAllSounds();
        DeleteAllMusic();
    }
}