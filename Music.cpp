#include "Music.h"
#include "ResourceSystem.h"
#include <iostream>

namespace RoguelikeGame
{
    Music::Music(const std::string& filename)
        : gameObject(new GameEngine::GameObject()),
        audioEngine(new GameEngine::AudioEngine(gameObject, GameEngine::AudioEngine::AudioType::Music))
    {
        Load(filename);
    }

    Music::~Music()
    {
        // ������� �����!
        delete audioEngine;
        delete gameObject;
    }

    bool Music::Load(const std::string& filename)
    {
        auto musicPtr = GameEngine::ResourceSystem::Instance()->GetMusic(filename);
        if (!musicPtr)
        {
            std::cerr << "Music file not found: " << filename << std::endl;
            return false;
        }

        audioEngine->SetAudio(musicPtr);
        return true;
    }

    void Music::Play()
    {
        audioEngine->Play();
    }

    void Music::SetFadeIn(float durationSec)
    {
        // ���������� �������� ���������
        // ����� ������������ sf::Clock � ��������� � Update()
    }

    void Music::Update(float deltaTime)
    {
        // ����� ����� ������������ ���� � ������ �������
    }
}