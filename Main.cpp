#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.h"
#include "Engine/Engine.h"
//#include <windows.h>
//#include <iostream>

int main()
{
	////Выделяем консоль и перенаправляем вывод
	//if (AllocConsole())
	//{
	//	FILE* fp;
	//	freopen_s(&fp, "CONOUT$", "w", stdout); //Перенаправляем stdout в консоль
	//	freopen_s(&fp, "CONOUT$", "w", stderr); //Перенаправляем stdout в консоль
	//}
	//else
	//{
	//	std::cerr << "Не удалось выделить консоль." << std::endl;
	//}

	Engine engine;
	engine.Initialize();
	engine.Run();


	GameState gameState;
	gameState.run();

	return 0;
}