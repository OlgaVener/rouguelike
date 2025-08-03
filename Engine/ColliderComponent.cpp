#include "pch.h"
#include <iostream>
#include "ColliderComponent.h"
#include "Trigger.h"

void GameEngine::ColliderComponent::OnTriggerExit(const GameEngine::Trigger& trigger)
{
	std::cout << "Trigger Exit between: "
		<< trigger.GetFirst() << " and " << trigger.GetSecond() << std::endl;
}
