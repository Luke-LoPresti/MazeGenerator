#include "InfoPanel.h"

#include <iostream>

static const std::string fontNames[] = { "MADE Soulmaze.otf", "Gobold Regular.otf" };
static const std::string controlTexts[] = { "Controls", "S - Start", "P - Pause", "R - Reset" };

InfoPanel::InfoPanel(int width, int height)
	: mWidth(width),
	  mHeight(height)
{
	loadResources();
}

InfoPanel::~InfoPanel()
{
}

void InfoPanel::draw(sf::RenderWindow* window) const
{
	sf::RectangleShape panelRect(sf::Vector2f((float)mWidth, (float)mHeight));
	panelRect.setFillColor(sf::Color::Black);

	panelRect.setOutlineThickness(-2.f);
	panelRect.setOutlineColor(sf::Color::White);

	window->draw(panelRect);

	auto titleText = createText("Maze\nGenerator", "MADE Soulmaze.otf", 18);
	titleText.setPosition(sf::Vector2f(10.f, 10.f));
	window->draw(titleText);

	drawControlText(window);
}

void InfoPanel::drawControlText(sf::RenderWindow* window) const
{
	int i = 0;
	for (const auto& controlText : controlTexts)
	{
		auto optionText = createText(controlText, "Gobold Regular.otf", 16);
		optionText.setPosition(sf::Vector2f(40.f, 80.f + (i++ * 30)));
		window->draw(optionText);
	}
}

void InfoPanel::loadResources()
{
	// load fonts into font map
	for (const auto& font : fontNames)
	{
		if (!mFonts[font].loadFromFile("resources/font/" + font))
		{
			std::cout << "Failed to load font: " << font << std::endl;
		}
	}
}

sf::Text InfoPanel::createText(const std::string& text, const std::string& font, uint32_t characterSize) const
{
	// check if font is loaded
	const auto sfFont = mFonts.find(font);
	if (sfFont == mFonts.end())
	{
		std::cout << "Font not loaded: " << font << std::endl;
		return sf::Text();
	}

	sf::Text sfText;
	sfText.setFont(sfFont->second);
	sfText.setCharacterSize(characterSize);
	sfText.setString(text);

	return sfText;
}