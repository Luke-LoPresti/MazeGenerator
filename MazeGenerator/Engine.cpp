#include "Engine.h"

// 60 frames per second
const sf::Time kTimePerFrame = sf::seconds(1.f / 60.f);

const uint32_t kWindowWidth = 800;
const uint32_t kWindowHeight = 480;

const uint32_t kInfoPanelWidth = 160;

const float kCellSize = 20.f;	// includes wall size
const float kWallSize = 2.f;	// cuts into cells size

Engine::Engine()
	: mWindow(sf::VideoMode(kWindowWidth, kWindowHeight), "Maze Generator")
{
	const int numRows = kWindowHeight / (int)kCellSize;
	const int numCols = (kWindowWidth - kInfoPanelWidth) / (int)kCellSize;

	mGrid = MazeGrid(numRows, numCols, kCellSize, kWallSize);

	mGrid.setPosition(sf::Vector2f(kInfoPanelWidth, 0.f));
	mGenerator = MazeGenerator(mGrid);

	mInfoPanel = InfoPanel(kInfoPanelWidth, kWindowHeight);
}

Engine::~Engine()
{
}

void Engine::run()
{
	// loop
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;	// init to 0

	while (mWindow.isOpen())
	{
		timeSinceLastUpdate += clock.restart();

		// perform the updates for each frame since the last update
		while (timeSinceLastUpdate > kTimePerFrame)
		{
			timeSinceLastUpdate -= kTimePerFrame;
			processEvents();
			update(kTimePerFrame);
		}

		render();
	}
}

void Engine::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			// close the window - exits game loop
			mWindow.close();
			break;

		case sf::Event::KeyPressed:
			handleKeyPressEvent(event.key.code);
			break;
		}
	}
}

void Engine::update(sf::Time deltaTime)
{
	mGenerator.update();
}

void Engine::render()
{
	mWindow.clear();

	mGrid.draw(&mWindow);
	mInfoPanel.draw(&mWindow);

	mWindow.display();
}

void Engine::handleKeyPressEvent(const sf::Keyboard::Key& key)
{
	if (key == sf::Keyboard::S)
	{
		mGenerator.start();
	}
	else if (key == sf::Keyboard::P)
	{
		mGenerator.togglePause();
	}
	else if (key == sf::Keyboard::R)
	{
		mGenerator.reset();
	}
}
