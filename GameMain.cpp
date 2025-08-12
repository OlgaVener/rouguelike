#include <SFML/Graphics.hpp>
#include "ResourceSystem.h"
#include "RenderSystem.h"
#include "Engine.h"
#include "Matrix2D.h"
#include "Player.h"
#include "LevelBuilder.h"

using namespace RoguelikeGame;
using namespace GameEngine;

void LoadGameResources()
{
    auto res = ResourceSystem::Instance();

    // Обычные текстуры
    res->LoadTexture("ball", "Resources/Textures/ball.png");

    // Атлас полов
    res->LoadTextureMap(
        "floors",
        "Resources/Textures/floor.png",
        sf::Vector2u(128, 128),
        4,
        true
    );

    // Атлас стен
    res->LoadTextureMap(
        "walls",
        "Resources/Textures/walls.png",
        sf::Vector2u(128, 128),
        4,
        true
    );
}

int main()
{
    RenderSystem::Instance()->SetMainWindow(
        new sf::RenderWindow(sf::VideoMode(1280, 720), "Roguelike")
    );

    LoadGameResources();

    LevelBuilder level;
    level.Start();

    Engine::Instance()->Run();

    return 0;
}
