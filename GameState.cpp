#include "GameState.h"
#include <iostream>
#include "Math.h"
#include "Constants.h"

TextureManager GameState::textureManager;

GameState::GameState()
	: window_(std::make_unique<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Arkanoid", sf::Style::Titlebar | sf::Style::Close))
	, stateScreen(StateScreen::Menu)
{
	initialize();
}

void GameState::initialize()
{
	setupWindow();
	loadResources();
	//initGameObjects();
	setupText();
	initMenu();
}

void GameState::loadResources()
{
	//// Глобальный менеджер текстур
	//textureManager.load("background", "resources/textures/background.png");
	//textureManager.load("ball", "resources/textures/ball.png");
	//textureManager.load("fireball", "resources/textures/fireball.png");
	//textureManager.load("fireball_bonus", "resources/textures/fireball_bonus.png");
	//textureManager.load("glass_blocks_bonus", "resources/textures/glass_blocks_bonus.png");
	//textureManager.load("platform", "resources/textures/platform.png");
	//textureManager.load("platform_bonus", "resources/textures/platform_bonus.png");
	//textureManager.load("brick_normal", "resources/textures/brick_normal.png");
	//textureManager.load("brick_strong", "resources/textures/brick_strong.png");
	//textureManager.load("brick_glass", "resources/textures/brick_glass.png");

	// // Настроки для спрайтов
	// ball_->getSprite().setScale(2.0f, 2.0f);

	// Загрузка текстур
	if (!font_.loadFromFile("resources/fonts/arial.ttf"))
	{
		throw std::runtime_error("Failed to load font");
	}
}

//void GameState::initGameObjects()
//{
//	// Установка текстуры заднего фона
//	background_.setTexture(textureManager.get("background"));
//	background_.setColor(sf::Color::White);	 // Белый цвет без затемнения
//
//}

void GameState::setupWindow()
{
	window_->setFramerateLimit(60);
	window_->setVerticalSyncEnabled(true);
}

void GameState::setupText()
{
	// TO BE DONE...
	placeholderText_.setFont(font_);
	placeholderText_.setCharacterSize(40);
	placeholderText_.setFillColor(sf::Color::White);
	placeholderText_.setString("TO BE DONE...\nPress Esc to exit to menu");
	centerText(placeholderText_);

	// Настройка текста "Вы проиграли"
	loseText_.setFont(font_);
	loseText_.setCharacterSize(40);
	loseText_.setFillColor(sf::Color::White);
	loseText_.setString("Game Over!\nTry again?\n(Space - Yes, Esc - No)");
	centerText(loseText_);

	// Настройка текста победы
	winText_.setFont(font_);
	winText_.setCharacterSize(40);
	winText_.setFillColor(sf::Color::White);
	winText_.setString("Congratulations! You won!\nPlay again?\n(Space - Yes, Esc - No)");
	centerText(winText_);
}

void GameState::centerText(sf::Text& text) const
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	text.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
}

void GameState::run()
{
	sf::Clock clock;

	while (window_->isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		if (stateScreen == StateScreen::Menu)
		{
			sf::Event event;

			while (window_->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window_->close();
				}

				menuState_->handleInput(event);
			}
			menuState_->render();
		}
		else if (stateScreen == StateScreen::GameWon)
		{
			handleScreenInput();
			showWinScreen();
		}
		else if (stateScreen == StateScreen::GameLost)
		{
			handleScreenInput();
			showLoseScreen();
		}
		else
		{
			handleEvents();
			update(deltaTime);
			render();
		}
	}
}

void GameState::handleEvents()
{
	sf::Event event;
	while (window_->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window_->close();
		}
	}
}

void GameState::update(float deltaTime)
{
	handleInput(deltaTime);
	// AccelerationBallSpeed(deltaTime); // Not used
	checkGameConditions();
}

void GameState::handleInput(float deltaTime) {
	float direction = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
		direction -= 1.f * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		direction += 1.f * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		stateScreen = StateScreen::Menu;
		menuState_->setActive(stateScreen);
	}
}

void GameState::initMenu()
{
	// Убедитесь, что font_ загружен!
	if (!font_.loadFromFile("resources/fonts/arial.ttf"))
	{
		throw std::runtime_error("Failed to load font");
	}

	// Создаём MenuState, передавая window_ и font_
	menuState_ = std::make_unique<MenuState>(*window_, font_);
	menuState_->setBackground(textureManager.get("background"));

	// Добавляем пункты меню
	menuState_->addMenuItem("TO BE DONE...", [this]() {tobedoneText(); });
	menuState_->addMenuItem("New Game", [this]() { startGame(); });
	menuState_->addMenuItem("Exit", [this]() { exitGame(); });

	menuState_->setActive(stateScreen);
}

void GameState::tobedoneText()
{
	stateScreen = StateScreen::Menu;
}

void GameState::startGame()
{
	stateScreen = StateScreen::Game;
	menuState_->setActive(stateScreen);
	resetGame();
}

void GameState::exitGame()
{
	window_->close();
}

void GameState::continueGame()
{
	stateScreen = StateScreen::Game;
	menuState_->setActive(stateScreen);
}

void GameState::checkGameConditions()
{
	checkLoseCondition();
	checkWinCondition();
}

void GameState::checkLoseCondition()
{
}

void GameState::checkWinCondition()
{
}

void GameState::checkCollisions()
{
}

void GameState::render()
{
	window_->clear();

	// Отрисовка фона
	window_->draw(background_);

	// Отрисовка текста "TO BE DONE..." в режиме игры
	if (stateScreen == StateScreen::Game)
		window_->draw(placeholderText_);

	// Отрисовка текста победы/поражения, если нужно
	if (stateScreen == StateScreen::GameWon)
		window_->draw(winText_);
	if (stateScreen == StateScreen::GameLost)
		window_->draw(loseText_);

	window_->display();
}

// TODO: Избавиться от дублирования кода
void GameState::showWinScreen()
{
	window_->clear();
	window_->draw(background_);
	window_->draw(winText_);
	window_->display();
}

void GameState::showLoseScreen()
{
	window_->clear();
	window_->draw(background_);
	window_->draw(loseText_);
	window_->display();
}
// TODO END: Избавиться от дублирования кода

void GameState::handleScreenInput()
{
	sf::Event event;
	while (window_->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window_->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				resetGame();
				stateScreen = StateScreen::Game;
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				stateScreen = StateScreen::Menu;
				menuState_->setActive(stateScreen);
			}
		}
	}
}

//void GameState::saveGame()
//{
//	GameSaveData saveData;
//	createSaveData(saveData);
//
//	if (saveSystem_.saveGame(SaveSystem::getDefaultSaveFilename(), saveData))
//	{
//		std::cout << "Game saved successfully!" << std::endl;
//	}
//	else
//	{
//		std::cerr << "Failed to save game!" << std::endl;
//	}
//}
//
//void GameState::loadGame()
//{
//	GameSaveData saveData;
//
//	if (saveSystem_.loadGame(SaveSystem::getDefaultSaveFilename(), saveData))
//	{
//		applySaveData(saveData);
//		stateScreen = StateScreen::Game;
//		menuState_->setActive(stateScreen);
//		std::cout << "Game loaded successfully!" << std::endl;
//	}
//	else
//	{
//		std::cerr << "Failed to load game!" << std::endl;
//	}
//}
//
//bool GameState::hasSavedGame() const
//{
//	return saveSystem_.saveExists(SaveSystem::getDefaultSaveFilename());
//}
//
//void GameState::createSaveData(GameSaveData& data)
//{
//}
//
//void GameState::applySaveData(const GameSaveData& data)
//{
//	
//}


void GameState::resetGame()
{
}
