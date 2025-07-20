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
        // ������������� ������
    }

    void Engine::Initialize()
    {
        // �������������� �������������
    }

    void Engine::Run()
    {
        auto& window = RenderSystem::Instance()->GetMainWindow();
        sf::Clock clock;

        while (window.isOpen())
        {
            // ��������� �������
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            // ������� ������ ������ ������
            window.clear(sf::Color::Black);

            // ���������� �������� ����
            float deltaTime = clock.restart().asSeconds();
            GameWorld::Instance()->Update(deltaTime);
            GameWorld::Instance()->Render();

            // �����������
            window.display();
        }
    }
}