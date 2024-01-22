#pragma once

#include <SFML/Graphics.hpp>
#include "SnakePart.h"
#include <vector>

class Appel
{
public:
	Appel(sf::RenderWindow& win_gui, float gridSize);
	sf::RectangleShape apple;

	void GenerateNewAppel(SnakePart headPart = {}, std::vector<SnakePart> body = {});
private:
	float gridSize;
	sf::RenderWindow& windowRef;
};

Appel::Appel(sf::RenderWindow& win_gui, float gridSize) : windowRef(win_gui) {
	this->gridSize = gridSize;
	this->apple.setSize(sf::Vector2f(gridSize, gridSize));
	this->apple.setFillColor(sf::Color::Red);

	GenerateNewAppel();
}

inline void Appel::GenerateNewAppel(SnakePart headPart, std::vector<SnakePart> body) {
	sf::Vector2u windowSize = windowRef.getSize();
	std::srand((unsigned)time(NULL));
	sf::Vector2f newAppelPosition{};

	while (true) {
		// Generate a new position for the apple
		float x = static_cast<float>(std::rand() % (windowSize.x / static_cast<int>(gridSize))) * gridSize;
		float y = static_cast<float>(std::rand() % (windowSize.y / static_cast<int>(gridSize))) * gridSize;

		newAppelPosition = sf::Vector2f(x, y);

		// Adds all the parts to the checkArray
		std::vector<SnakePart> checkArray{};
		for (SnakePart snakePart : body) {
			if (snakePart.part.getPosition() != newAppelPosition) {
				checkArray.push_back(snakePart);
			}
		}

		if (headPart.part.getPosition() != newAppelPosition) {
			checkArray.push_back(headPart);
		}

		// If all the parts has been added to the checkArray that means that the apple is generated in a new position
		if (checkArray.size() == body.size() + 1) break;
	}

	apple.setPosition(newAppelPosition);
}