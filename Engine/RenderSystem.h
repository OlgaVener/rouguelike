#pragma once
#include <SFML/Graphics.hpp>

namespace GameEngine
{
    class RenderSystem
    {
    public:
        static RenderSystem* Instance();

        void SetMainWindow(sf::RenderWindow* newWindow);
        sf::RenderWindow& GetMainWindow() const;
        void Render(const sf::Drawable& drawable);

    private:
        sf::RenderWindow* window = nullptr;  // явна€ инициализаци€
    };
}