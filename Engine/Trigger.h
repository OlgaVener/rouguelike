#pragma once

namespace GameEngine
{
	class ColliderComponent;
	struct Trigger
	{
	public:
		Trigger(ColliderComponent* newFirst, ColliderComponent* newSecond) :
			first(newFirst), second(newSecond)
		{
		};
	private:
		ColliderComponent* first;
		ColliderComponent* second;
	};
}
