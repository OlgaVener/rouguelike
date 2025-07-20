#include "pch.h"
#include "Engine.h"
#include "GameWorld.h"
#include "RenderSystem.h"

namespace GameEngine
{
    Engine* Engine::Instance()
    {
        static Engine instance;
        return &instance;
    }

    Engine::Engine()
    {
        // Инициализация движка
    }

    void Engine::Initialize()
    {
        // Дополнительная инициализация
    }

    void Engine::Run()
    {
        auto& window = RenderSystem::Instance()->GetMainWindow();
        sf::Clock clock;

        while (window.isOpen())
        {
            // Обработка событий
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            // Очистка экрана черным цветом
            window.clear(sf::Color::Black);

            // Обновление игрового мира
            float deltaTime = clock.restart().asSeconds();
            GameWorld::Instance()->Update(deltaTime);
            GameWorld::Instance()->Render();

            // Отображение
            window.display();
        }
    }
}