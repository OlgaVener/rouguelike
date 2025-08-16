#include "pch.h"
#include "AudioEngine.h"
#include "GameObject.h"
#include <SFML/Audio.hpp>

namespace GameEngine
{
    AudioEngine::AudioEngine(GameObject* gameObject, AudioType type)
        : Component(gameObject), type(type), sound(nullptr), music(nullptr)
    {
        if (type == AudioType::Sound)
            sound = new sf::Sound();
    }

    AudioEngine::~AudioEngine()
    {
        if (sound) delete sound;
    }

    void AudioEngine::SetAudio(const sf::SoundBuffer& audio)
    {
        if (sound) sound->setBuffer(audio);
    }

    void AudioEngine::SetAudio(sf::Music* musicPtr)
    {
        music = musicPtr;
    }

    void AudioEngine::SetLoop(bool loop)
    {
        if (type == AudioType::Sound && sound) sound->setLoop(loop);
        if (type == AudioType::Music && music) music->setLoop(loop);
    }

    void AudioEngine::SetVolume(float volume)
    {
        if (type == AudioType::Sound && sound) sound->setVolume(volume);
        if (type == AudioType::Music && music) music->setVolume(volume);
    }

    void AudioEngine::Play()
    {
        if (type == AudioType::Sound && sound) sound->play();
        if (type == AudioType::Music && music) music->play();
    }

    void AudioEngine::Stop()
    {
        if (type == AudioType::Sound && sound) sound->stop();
        if (type == AudioType::Music && music) music->stop();
    }

    void AudioEngine::Pause()
    {
        if (type == AudioType::Sound && sound) sound->pause();
        if (type == AudioType::Music && music) music->pause();
    }
}
