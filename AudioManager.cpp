#include "AudioManager.h"
#include "ResourceSystem.h"

namespace RoguelikeGame
{
    AudioManager& AudioManager::Instance()
    {
        static AudioManager instance;
        return instance;
    }

    void AudioManager::Initialize()
    {
        // Создаем звуковые объекты
        backgroundMusic = std::make_shared<Sound>("background_music");
        backgroundMusic->SetLoop(true);
        backgroundMusic->SetVolume(50.0f);

        sounds["step"] = std::make_shared<Sound>("player_step");
        sounds["attack"] = std::make_shared<Sound>("player_attack");
        sounds["hit"] = std::make_shared<Sound>("player_hit");
        sounds["wall_hit"] = std::make_shared<Sound>("wall_hit");
        sounds["enemy_attack"] = std::make_shared<Sound>("enemy_attack");

        // Настраиваем громкость звуков
        for (auto& sound : sounds) {
            sound.second->SetVolume(70.0f);
        }
    }

    void AudioManager::PlayBackgroundMusic()
    {
        if (backgroundMusic) {
            backgroundMusic->Play();
        }
    }

    void AudioManager::PlaySound(const std::string& soundName)
    {
        if (sounds.find(soundName) != sounds.end()) {
            sounds[soundName]->Play();
        }
    }

    void AudioManager::StopAllSounds()
    {
        if (backgroundMusic) {
            backgroundMusic->Stop();
        }
        for (auto& sound : sounds) {
            sound.second->Stop();
        }
    }

    void AudioManager::SetMusicVolume(float volume)
    {
        if (backgroundMusic) {
            backgroundMusic->SetVolume(volume);
        }
    }

    void AudioManager::SetSoundsVolume(float volume)
    {
        for (auto& sound : sounds) {
            sound.second->SetVolume(volume);
        }
    }
}