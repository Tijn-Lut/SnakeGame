#pragma once

#include <vector>
#include "DifficultyButton.h"

class MainMenu
{
public:
	MainMenu(sf::RenderWindow& windowRef);

	void Open();
    void HandleMouseButtonPressed(sf::Event& event, float& moveInterval);

    bool mainMenuIsOpen = true;
private:
	void GenerateButtons();

	sf::RenderWindow& windowRef;
    sf::Font font;
    std::vector<DifficultyButton> difficultyButtons;
};

MainMenu::MainMenu(sf::RenderWindow& windowRef)
	: windowRef(windowRef)
{
    if (!font.loadFromFile("JetBrainsMono.ttf")) {
        std::cout << "The file 'JetBrainsMono.ttf' could not be found";
    }

    GenerateButtons();
}

void MainMenu::Open()
{
    windowRef.clear();

    // Draw buttons
    for (DifficultyButton diffButton : difficultyButtons) {
        diffButton.button.Draw(windowRef);
    }

    windowRef.display();
}

void MainMenu::HandleMouseButtonPressed(sf::Event& event, float& moveInterval)
{
    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(windowRef);

        for (DifficultyButton diffButton : difficultyButtons) {
            bool mouseInButton = mousePos.x >= diffButton.button.GetPosition().x - diffButton.button.GetGlobalBounds().width / 2
                && mousePos.x <= diffButton.button.GetPosition().x + diffButton.button.GetGlobalBounds().width / 2
                && mousePos.y >= diffButton.button.GetPosition().y - diffButton.button.GetGlobalBounds().height / 2
                && mousePos.y <= diffButton.button.GetPosition().y + diffButton.button.GetGlobalBounds().height / 2;

            if (mouseInButton) {
                moveInterval = diffButton.moveInterval;
                mainMenuIsOpen = false;
                break;
            }
        }
    }
}

void MainMenu::GenerateButtons()
{
    // Set up buttons
    difficultyButtons.push_back(DifficultyButton(font, "Easy", 30, sf::Color::White, sf::Color::Green, sf::Vector2f(50.f, 50.f), 0.15f));
    difficultyButtons.push_back(DifficultyButton(font, "Medium", 30, sf::Color::White, sf::Color::Green, sf::Vector2f(50.f, 150.f), 0.1f));
    difficultyButtons.push_back(DifficultyButton(font, "Hard", 30, sf::Color::White, sf::Color::Green, sf::Vector2f(50.f, 250.f), 0.05f));
}