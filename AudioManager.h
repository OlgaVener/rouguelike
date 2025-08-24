// AudioManager.h
#pragma once
#include "Sound.h"
#include <unordered_map>

namespace RoguelikeGame
{
    class AudioManager
    {
    private:
        std::unordered_map<std::string, std::shared_ptr<Sound>> sounds;
        std::shared_ptr<Sound> backgroundMusic;

    public:
        static AudioManager& Instance();

        void Initialize();
        void PlayBackgroundMusic();
        void PlaySound(const std::string& soundName);
        void StopAllSounds();

        void SetMusicVolume(float volume);
        void SetSoundsVolume(float volume);
    };
}
