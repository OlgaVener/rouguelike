#include "pch.h"
#include "Engine.h"
#include <iostream>
Engine::Engine() {}
void Engine::Initialize()
{
	std::cout << "Engine Init" << std::endl;
}
void Engine::Run()
{
	std::cout << "Engine runs!" << std::endl;
}
