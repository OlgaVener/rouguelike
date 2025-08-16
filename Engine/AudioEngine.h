#pragma once
#include <SFML/Audio.hpp>
#include "Component.h"

namespace GameEngine
{
    class AudioEngine : public Component
    {
    public:
        enum class AudioType { Sound, Music };

        AudioEngine(GameObject* gameObject, AudioType type = AudioType::Sound);
        ~AudioEngine();

        void SetAudio(const sf::SoundBuffer& audio);
        void SetAudio(sf::Music* musicPtr);         

        void SetLoop(bool loop);
        void SetVolume(float volume);

        void Play();
        void Stop();
        void Pause();

    private:
        AudioType type;
        sf::Sound* sound;
        sf::Music* music;
    };
}
