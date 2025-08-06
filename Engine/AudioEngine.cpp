#include "pch.h"
#include "AudioEngine.h"

GameEngine::AudioEngine::AudioEngine(GameObject* gameObject) : Component(gameObject)
{
	sound = new sf::Sound();
}

GameEngine::AudioEngine::~AudioEngine()
{
	sound->stop();
	delete sound;
}

void GameEngine::AudioEngine::Update(float deltaTime)
{
}

void GameEngine::AudioEngine::Render()
{
}

void GameEngine::AudioEngine::SetAudio(const sf::SoundBuffer& audio)
{
	sound->setBuffer(audio);
}

void GameEngine::AudioEngine::SetLoop(bool loop)
{
	sound->setLoop(loop);
}

void GameEngine::AudioEngine::SetVolume(float volume)
{
	sound->setVolume(volume);
}

void GameEngine::AudioEngine::AudioPlay()
{
	if (sound->getStatus() != sf::SoundSource::Playing)
	{
		sound->play();
	}
}

void GameEngine::AudioEngine::AudioStop()
{
	sound->stop();
}

void GameEngine::AudioEngine::AudioPause()
{
	sound->pause();
}

void GameEngine::AudioEngine::AudioResume()
{
	if (sound->getStatus() != sf::SoundSource::Playing)
	{
		sound->play();
	}
}
