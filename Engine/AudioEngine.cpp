#include "pch.h"
#include "AudioEngine.h"
#include "GameObject.h"
#include <SFML/Audio.hpp>

namespace GameEngine
{
    AudioEngine::AudioEngine(GameObject* gameObject) 
        : Component(gameObject)
    {
        sound = new sf::Sound();
    }

    //Очистка
    AudioEngine::~AudioEngine()
    {
        sound->stop();
        delete sound;
    }

    //Обновление
    void AudioEngine::Update(float deltaTime)
    {
    }

    //Визуализация
    void AudioEngine::Render()
    {
    }

    //Подключение аудио-файла
    void AudioEngine::SetAudio(const sf::SoundBuffer& audio)
    {
        sound->setBuffer(audio);
    }
    
    //Зацикливание звука
    void AudioEngine::SetLoop(bool loop)
    {
        sound->setLoop(loop);
    }

    //Настройка громкости
    void AudioEngine::SetVolume(float volume)
    {
        sound->setVolume(volume);
    }

    //Воспроизведение
    void AudioEngine::Play()
    {
        if (sound->getStatus() != sf::SoundSource::Playing)
        {
            sound->play();
        }
    }

    //Остановка
    void AudioEngine::Stop()
    {
        sound->stop();
    }

    //Пауза
    void AudioEngine::Pause()
    {
        sound->pause();
    }

    //Продолжить
    void AudioEngine::Resume()
    {
        if (sound->getStatus() != sf::SoundSource::Playing)
        {
            sound->play();
        }
    }
}
