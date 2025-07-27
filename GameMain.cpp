#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include "Matrix2D.h"

using namespace RoguelikeGame;

int main()
{
	RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "Roguelike"));

	ResourceSystem::Instance()->LoadTexture("ball", "Resources/Textures/ball.png");

	auto developerLevel = std::make_shared<DeveloperLevel>();
	developerLevel->Start();

	GameEngine::Matrix2D zeroMatrix;
	zeroMatrix.Print();

	GameEngine::Matrix2D translationMatrix = GameEngine::Matrix2D(Vector2Df(12.f, 5.f), 0.f, Vector2Df(1.f, 1.f));
	translationMatrix.Print();

	GameEngine::Matrix2D rotationMatrix = GameEngine::Matrix2D(Vector2Df(0.f, 0.f), 90.f, Vector2Df(1.f, 1.f));
	rotationMatrix.Print();

	(rotationMatrix * translationMatrix).Print();

	GameEngine::Matrix2D someMatrix = GameEngine::Matrix2D(Vector2Df(13.f, 25.f), 90.f, Vector2Df(1.5f, 1.f));
	someMatrix.Print();

	(someMatrix * someMatrix.GetInversed()).Print();

	Engine::Instance()->Run();

	return 0;
}