#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.h"
#include "Engine/Engine.h"
//#include <windows.h>
//#include <iostream>

int main()
{
	////�������� ������� � �������������� �����
	//if (AllocConsole())
	//{
	//	FILE* fp;
	//	freopen_s(&fp, "CONOUT$", "w", stdout); //�������������� stdout � �������
	//	freopen_s(&fp, "CONOUT$", "w", stderr); //�������������� stdout � �������
	//}
	//else
	//{
	//	std::cerr << "�� ������� �������� �������." << std::endl;
	//}

	Engine engine;
	engine.Initialize();
	engine.Run();


	GameState gameState;
	gameState.run();

	return 0;
}