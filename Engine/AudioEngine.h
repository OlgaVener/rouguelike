#pragma once
#include <SFML/Audio.hpp>
#include "Component.h"

namespace GameEngine
{
    class AudioEngine : public Component
    {
    public:
        AudioEngine(GameObject* gameObject);
        ~AudioEngine();

        void Update(float deltaTime);
        void Render();

        void SetAudio(const sf::SoundBuffer& audio);       

        void SetLoop(bool loop);
        void SetVolume(float volume);

        void Play();
        void Stop();
        void Pause();
        void Resume();

    private:
        sf::Sound* sound;
        sf::Music* music;
    };
}
