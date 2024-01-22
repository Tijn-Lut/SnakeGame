#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <vector>
#include "Appel.h"
#include "SnakePart.h"

class Snake
{
public:
	Snake(sf::RenderWindow& win_gui, float gridSize);
	short moveDirection;
	int highScore;
	int score;
	int length = 2;
	bool gameOver = false;

	void Move();
	void Grow(sf::Vector2f headPosition);
	void CheckCollition(sf::Vector2f headPosition);
	void Render();
	void GameOver();
	void LoadScoreFromFile();
	void Reset();
private:
	float gridSize;
	sf::RenderWindow& windowRef;
	SnakePart headPart;
	std::vector<SnakePart> body;
	Appel appelObj;

	sf::SoundBuffer deathSoundBuffer;
	sf::Sound deathSound;

	sf::SoundBuffer eatSoundBuffer;
	sf::Sound eatSound;

	bool savedHighScore;
};

Snake::Snake(sf::RenderWindow& windowRef, float gridSize)
	: windowRef(windowRef),
	headPart(gridSize, sf::Color(0, 100, 0)),
	appelObj(windowRef, gridSize)
{
	LoadScoreFromFile();
	this->gridSize = gridSize;
	this->moveDirection = 1;

	if (!deathSoundBuffer.loadFromFile("SnakeDeath.wav")) {
		std::cout << "SnakeDeath.wav file could not be loaded";
	}
	deathSound.setBuffer(deathSoundBuffer);

	if (!eatSoundBuffer.loadFromFile("EatingAppel.wav")) {
		std::cout << "EatingAppel.wav file could not be loaded";
	}
	eatSound.setBuffer(eatSoundBuffer);
}

void Snake::Move()
{
	sf::Vector2f headPosition = headPart.part.getPosition();
	sf::Vector2f newHeadPosition;

	switch (moveDirection)
	{
	case 1:
		newHeadPosition = sf::Vector2f(headPosition.x + gridSize, headPosition.y);
		break;
	case 2:
		newHeadPosition = sf::Vector2f(headPosition.x, headPosition.y + gridSize);
		break;
	case 3:
		newHeadPosition = sf::Vector2f(headPosition.x - gridSize, headPosition.y);
		break;
	default:
		newHeadPosition = sf::Vector2f(headPosition.x, headPosition.y - gridSize);
		break;
	}

	CheckCollition(headPart.part.getPosition());

	if (body.size() <= length) {
		Grow(headPosition);
	}

	if (body.size() > length) {
		body.erase(body.begin());
	}

	headPart.part.setPosition(newHeadPosition);
}

void Snake::Grow(sf::Vector2f headPosition)
{
	// Add a new part to the body
	SnakePart snakePart(gridSize, sf::Color::Green);
	snakePart.part.setPosition(headPosition.x, headPosition.y);
	body.push_back(snakePart);
}

void Snake::CheckCollition(sf::Vector2f headPosition)
{
	sf::Vector2u windowSize = windowRef.getSize();
	if (headPosition.y < 0.f || headPosition.y >= windowSize.y || headPosition.x < 0.f || headPosition.x >= windowSize.x)
	{
		GameOver();
	}

	for (SnakePart snakePart : body) {
		if (snakePart.part.getPosition() == headPosition) {
			GameOver();
		}
	}

	if (headPosition == appelObj.apple.getPosition()) {
		eatSound.play();
		length++;
		score++;
		if (!savedHighScore || score > highScore) {
			highScore = score;
		}
		appelObj.GenerateNewAppel(headPart, body);
	}
}

void Snake::Render()
{
	windowRef.clear();
	for (SnakePart snakePart : body)
	{
		windowRef.draw(snakePart.part);
	}
	windowRef.draw(appelObj.apple);
	windowRef.draw(headPart.part);
}

void Snake::GameOver()
{
	if (score >= highScore) {
		std::ofstream outputFile("HighScore.txt");
		if (outputFile.is_open())
		{
			outputFile << score;
			outputFile.close();
		}
		else
		{
			std::cerr << "Unable to open file for saving score." << std::endl;
		}
	}

	deathSound.play();
	gameOver = true;
}

void Snake::LoadScoreFromFile()
{
	std::ifstream inputFile("HighScore.txt");
	if (inputFile.is_open())
	{
		savedHighScore = true;
		inputFile >> highScore;
		inputFile.close();
	}
	else
	{
		std::cerr << "Unable to open file for loading score. Setting default length." << std::endl;
		highScore = 0;
		savedHighScore = false;
	}
}

void Snake::Reset()
{
	headPart.part.setPosition(sf::Vector2f(0.f, 0.f));
	body = {};
	length = 2;
	score = 0;
	moveDirection = 1;
	gameOver = false;
}
