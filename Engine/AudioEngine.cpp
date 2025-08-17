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

    //�������
    AudioEngine::~AudioEngine()
    {
        sound->stop();
        delete sound;
    }

    //����������
    void AudioEngine::Update(float deltaTime)
    {
    }

    //������������
    void AudioEngine::Render()
    {
    }

    //����������� �����-�����
    void AudioEngine::SetAudio(const sf::SoundBuffer& audio)
    {
        sound->setBuffer(audio);
    }
    
    //������������ �����
    void AudioEngine::SetLoop(bool loop)
    {
        sound->setLoop(loop);
    }

    //��������� ���������
    void AudioEngine::SetVolume(float volume)
    {
        sound->setVolume(volume);
    }

    //���������������
    void AudioEngine::Play()
    {
        if (sound->getStatus() != sf::SoundSource::Playing)
        {
            sound->play();
        }
    }

    //���������
    void AudioEngine::Stop()
    {
        sound->stop();
    }

    //�����
    void AudioEngine::Pause()
    {
        sound->pause();
    }

    //����������
    void AudioEngine::Resume()
    {
        if (sound->getStatus() != sf::SoundSource::Playing)
        {
            sound->play();
        }
    }
}
