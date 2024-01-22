#pragma once

#include <SFML/Graphics.hpp>

class SnakePart
{
public:
	SnakePart();
	SnakePart(float gridSize, sf::Color color);

	sf::RectangleShape part;
};

SnakePart::SnakePart()
{

}

SnakePart::SnakePart(float gridSize, sf::Color color) {
	part.setFillColor(color);
	part.setSize(sf::Vector2f(gridSize, gridSize));
}