#pragma once
#include "AudioEngine.h"
#include "GameObject.h"
#include <string>

namespace RoguelikeGame
{
    class Music
    {
    public:
        explicit Music(const std::string& filename);
        ~Music();

        bool Load(const std::string& filename);

        void Play();
        void SetFadeIn(float durationSec);
        void Update(float deltaTime);
        void Stop();
        void Pause();
        void SetVolume(float volume);
        void SetLoop(bool loop);

    private:
        GameEngine::GameObject* gameObject = nullptr;
        GameEngine::AudioEngine* audioEngine = nullptr;
    };
}
