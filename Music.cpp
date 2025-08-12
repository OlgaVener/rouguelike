#include "Music.h"

RoguelikeGame::Music::Music(const std::string& musicName)
{
    // ������� ������� ������ ��� �����
    gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("Music");

    // ��������� ��������� AudioEngine
    audioEngine = gameObject->AddComponent<GameEngine::AudioEngine>();

    // ��������� �������� ����� ����� ResourceSystem
    soundBuffer = GameEngine::ResourceSystem::Instance()->GetSoundBufferShared(musicName);

    // ������������� �����
    if (soundBuffer)
    {
        audioEngine->SetAudio(*soundBuffer);
    }
}

RoguelikeGame::Music::~Music()
{
    // ������������� ������ ��� �����������
    audioEngine->AudioStop();
}

void RoguelikeGame::Music::Play()
{
    audioEngine->AudioPlay();
}

void RoguelikeGame::Music::Stop()
{
    audioEngine->AudioStop();
}

void RoguelikeGame::Music::Pause()
{
    audioEngine->AudioPause();
}

void RoguelikeGame::Music::SetVolume(float volume)
{
    audioEngine->SetVolume(volume);
}

void RoguelikeGame::Music::SetLoop(bool loop)
{
    audioEngine->SetLoop(loop);
}