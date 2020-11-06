#pragma once
#include <SFML/Graphics.hpp>

#include "MazeGenerator.h"
#include "InfoPanel.h"

class Engine
{
public:
	Engine();
	~Engine();

	void run();

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

	void handleKeyPressEvent(const sf::Keyboard::Key& key);

	sf::RenderWindow mWindow;

	MazeGrid mGrid;
	MazeGenerator mGenerator;

	InfoPanel mInfoPanel;
};

