#include "LevelBuilder.h"
#include "Wall.h"

using namespace GameEngine;

void GameEngine::LevelBuilder::Start()
{
	int width = 15;
	int height = 15;

	for (int y = 0; y < height + 1; ++y)
	{
		player = std::make_unique<Player>(std::forward<GameEngine::Vector2Df>({ width / 2 * 128.f, height / 2 * 128.f }));
		ai = std::make_unique<RoguelikeGame::EnemyAI>(std::forward<GameEngine::Vector2Df>({ width / 3 * 128.f, height / 3 * 128.f }), player->GetGameObject());
		music = std::make_unique<Music>("music");
	}
}

void GameEngine::LevelBuilder::Restart()
{
	Stop();
	Start();
}

void GameEngine::LevelBuilder::Stop()
{
	GameWorld::Instance()->Clear();
}
