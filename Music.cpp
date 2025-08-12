#include "Music.h"
#include <iostream>

namespace RoguelikeGame
{
    Music::Music(const std::string& musicName)
    {
        gameObject = new GameEngine::GameObject();
        audioEngine = new GameEngine::AudioEngine(gameObject, GameEngine::AudioEngine::AudioType::Music);

        auto musicPtr = GameEngine::ResourceSystem::Instance()->GetMusic(musicName);
        if (musicPtr)
        {
            audioEngine->SetAudio(musicPtr);
        }
        else
        {
            std::cerr << "Музыка не найдена: " << musicName << std::endl;
        }
    }

    Music::~Music()
    {
        delete audioEngine;
        delete gameObject;
    }

    void Music::Play() { audioEngine->Play(); }
    void Music::Stop() { audioEngine->Stop(); }
    void Music::Pause() { audioEngine->Pause(); }

    void Music::SetVolume(float volume) { audioEngine->SetVolume(volume); }
    void Music::SetLoop(bool loop) { audioEngine->SetLoop(loop); }
}
