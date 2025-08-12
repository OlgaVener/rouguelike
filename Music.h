#pragma once
#include <SFML/Audio.hpp>
#include "AudioEngine.h"
#include "ResourceSystem.h"
#include "GameObject.h"

namespace RoguelikeGame
{
    class Music
    {
    public:
        Music(const std::string& musicName);
        ~Music();

        void Play();
        void Stop();
        void Pause();
        void SetVolume(float volume);
        void SetLoop(bool loop);

    private:
        GameEngine::GameObject* gameObject;
        GameEngine::AudioEngine* audioEngine;
    };
}
