#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <string>
#include <unordered_map>
#include "Component.h"

namespace GameEngine
{
    class AudioEngine : public Component 
    {
    public:
        AudioEngine(GameObject* gameObject);
        ~AudioEngine();

        void Update(float deltaTime) override;
        void Render() override;

        void SetAudio(const sf::SoundBuffer& audio);
        void SetLoop(bool loop);

        void SetVolume(float volume);
        void AudioPlay();
        void AudioStop();
        void AudioPause();
        void AudioResume();
    private:
        sf::Sound* sound;
    };
}