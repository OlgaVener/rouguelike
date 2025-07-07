#pragma once
#include "TextureManager.h"
#include "MenuState.h"
#include "Constants.h"


enum class StateScreen  // Состояние экрана
{
	Game,
	Menu,
	Records,
	GameWon,
	GameLost
};

class GameState
{
public:
	GameState();  // Конструктор
	void run();	  // Запуск главного игрового цикла

private:
	// === Инициализация и настройки ===
	void initialize();						// Общая инициализация игры
	void setupWindow();						// Настройка окна SFML
	void loadResources();					// Загрузка текстур, шрифтов и т.п.
	//void initGameObjects();					// Создание объектов: платформа, мяч, кирпичи
	void setupText();						// Настройка текста (очки, победа, поражение)
	void centerText(sf::Text& text) const;	// Центрирование текста по экрану

	// === Игровая логика ===

	void handleEvents();						  // Обработка событий (ввод, закрытие)
	void update(float deltaTime);				  // Обновление логики игры
	void render();								  // Отрисовка кадра
	void handleInput(float deltaTime);			  // Обработка клавиш

	// === Проверка условий завершения игры ===
	void checkGameConditions();	 // Проверка: выигрыш или проигрыш
	void checkLoseCondition();	 // Условие проигрыша
	void checkWinCondition();	 // Условие победы

	// === Проверка коллизий ===
	void checkCollisions();

	// === Экран победы/поражения ===
	void showWinScreen();	   // Показать экран победы
	void handleScreenInput();  // Обработка ввода на экране победы
	void showLoseScreen();	   // Показать экран поражения
	// void handleLoseScreenInput();  // Обработка ввода на экране поражения
	void resetGame();  // Сбросить игру в начальное состояние

	//// === Система сохранения/загрузки ===
	//void saveGame();			   // Сохранить текущее состояние игры
	//void loadGame();			   // Загрузить состояние игры  
	//bool hasSavedGame() const;     // Проверить наличие сохранения
	////void createSaveData(GameSaveData& data); // Создать данные для сохранения
	////void applySaveData(const GameSaveData& saveData); // Применить загруженные данные



	// === Ресурсы и отображение ===
	static TextureManager textureManager;  // Менеджер текстур
	
	sf::Font font_;						   // Используемый шрифт
	sf::Text placeholderText_;
	sf::Text winText_;					   // Текст победы
	sf::Text loseText_;					   // Текст поражения
	sf::Sprite background_;				   // Задний фон
	//SaveSystem saveSystem_;                // Система сохранений

	// === Игровые объекты ===
	std::unique_ptr<sf::RenderWindow> window_;	  // Основное окно SFML
	
	std::unique_ptr<MenuState> menuState_;	      // Экран меню

	// === Меню ===
	void initMenu();						      // Инициализация меню
	void tobedoneText();
	void startGame();						      // Новая игра
	void exitGame();							  // Выход
	void continueGame();						  // Продолжить игру

	// === Состояния игры ===
	StateScreen stateScreen;  // Состояние экрана
	// === Параметры физики ===
												  // Test Fireball mechanic
	// sf::Clock bonusClockTimer_;
	// BonusType currentBonusActivity = BonusType::None;
	
};