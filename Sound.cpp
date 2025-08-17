#include "Sound.h"
#include <iostream>

namespace RoguelikeGame
{
    Sound::Sound(const std::string& soundName)
    {
        gameObject = new GameEngine::GameObject();
        audioEngine = new GameEngine::AudioEngine(gameObject);

        auto soundBuffer = GameEngine::ResourceSystem::Instance()->GetSoundBuffer(soundName);
        if (soundBuffer)
        {
            audioEngine->SetAudio(*soundBuffer);
        }
        else
        {
            std::cerr << "«вук не найден: " << soundName << std::endl;
        }
    }

    Sound::~Sound()
    {
        delete audioEngine;
        delete gameObject;
    }

    void Sound::Play() { audioEngine->Play(); }
    void Sound::Stop() { audioEngine->Stop(); }
    void Sound::Pause() { audioEngine->Pause(); }

    void Sound::SetVolume(float volume) { audioEngine->SetVolume(volume); }
    void Sound::SetLoop(bool loop) { audioEngine->SetLoop(loop); }
}
