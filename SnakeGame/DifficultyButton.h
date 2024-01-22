#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"

class DifficultyButton
{
public:
	DifficultyButton(sf::Font& font, std::string string, int characterSize, sf::Color textColor, sf::Color backGroundColor, sf::Vector2f position, float moveInterval);

	Button button;
	float moveInterval;
};

DifficultyButton::DifficultyButton(sf::Font& font, std::string string, int characterSize, sf::Color textColor, sf::Color backGroundColor, sf::Vector2f position, float moveInterval)
{
	this->button = Button(font, string, characterSize, textColor, backGroundColor, position);
	this->moveInterval = moveInterval;
}