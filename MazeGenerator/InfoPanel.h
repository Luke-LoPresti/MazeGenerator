#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

class InfoPanel
{
public:
	InfoPanel(int width, int height);
	InfoPanel() = default;
	~InfoPanel();

	void draw(sf::RenderWindow* window) const;
	void drawControlText(sf::RenderWindow* window) const;

private:
	void loadResources();
	sf::Text createText(const std::string& text, const std::string& font, uint32_t characterSize) const;

	int mWidth;
	int mHeight;

	std::unordered_map<std::string, sf::Font> mFonts;
};

