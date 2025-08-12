#include "Music.h"

RoguelikeGame::Music::Music(const std::string& musicName)
{
    // Создаем игровой объект для аудио
    gameObject = GameEngine::GameWorld::Instance()->CreateGameObject("Music");

    // Добавляем компонент AudioEngine
    audioEngine = gameObject->AddComponent<GameEngine::AudioEngine>();

    // Загружаем звуковой буфер через ResourceSystem
    soundBuffer = GameEngine::ResourceSystem::Instance()->GetSoundBufferShared(musicName);

    // Устанавливаем аудио
    if (soundBuffer)
    {
        audioEngine->SetAudio(*soundBuffer);
    }
}

RoguelikeGame::Music::~Music()
{
    // Останавливаем музыку при уничтожении
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