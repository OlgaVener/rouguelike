#include "DeveloperLevel.h"

using namespace Engine;

namespace RoguelikeGame
{
	void DeveloperLevel::Start()
	{
		player = std::make_shared<Player>();
	}
	void DeveloperLevel::Restart()
	{
		Stop();
		Start();
	}
	void DeveloperLevel::Stop()
	{
		GameWorld::Instance()->Clear();
	}
}