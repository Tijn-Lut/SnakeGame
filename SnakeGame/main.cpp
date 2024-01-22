#include <iostream>
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Snake.h"

int WinMain()
{
    const short WINDOW_WIDTH = 1400;
    const short WINDOW_HEIGHT = 800;
    const float GRID_SIZE = 50.f;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake!");

    float moveInterval = NULL;
    MainMenu mainMenuObj(window);

    Snake snakeObj(window, GRID_SIZE);
    int newMoveDirection = 4;

    sf::Music music;
    if (!music.openFromFile("MainTheme.flac")) {
        std::cout << "The file 'MainTheme.flac' could not be found";
    }
    music.setVolume(20.f);
    music.setLoop(true);
    music.play();

    sf::Clock clock;
    float elapsedTime = 0.f;

    // Settings for the text scores text
    sf::Font font;
    if (!font.loadFromFile("JetBrainsMono.ttf")) {
        window.close();
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setPosition(sf::Vector2f(0.f, 0.f));

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(64);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(sf::Vector2f(0.f, 0.f));
    gameOverText.setString("GAME OVER!");
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    gameOverText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f));

    sf::Text gameOverScoreText;
    gameOverScoreText.setFont(font);
    gameOverScoreText.setCharacterSize(32);
    gameOverScoreText.setFillColor(sf::Color::White);
    gameOverScoreText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 100.0f)); // Adjust the position

    sf::RectangleShape buttonShape(sf::Vector2f(200.f, 50.f)); // Adjust the size of the button
    buttonShape.setFillColor(sf::Color::Green);
    buttonShape.setOutlineColor(sf::Color::White);
    buttonShape.setOutlineThickness(2.f);
    buttonShape.setOrigin(buttonShape.getSize() / 2.0f);
    buttonShape.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 200.0f)); // Adjust the position

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setStyle(sf::Text::Bold);
    buttonText.setPosition(buttonShape.getPosition());
    buttonText.setString("Restart");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (mainMenuObj.mainMenuIsOpen) {
                    mainMenuObj.HandleMouseButtonPressed(event, moveInterval);
                }
                else if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    bool mouseInButton = mousePos.x >= buttonShape.getPosition().x - buttonShape.getGlobalBounds().width / 2
                        && mousePos.x <= buttonShape.getPosition().x + buttonShape.getGlobalBounds().width / 2
                        && mousePos.y >= buttonShape.getPosition().y - buttonShape.getGlobalBounds().height / 2
                        && mousePos.y <= buttonShape.getPosition().y + buttonShape.getGlobalBounds().height / 2;

                    if (mouseInButton) {
                        // Restart the game when the button is clicked
                        snakeObj.Reset();
                    }
                }
                break;
            }
        }

        if (mainMenuObj.mainMenuIsOpen) {
            mainMenuObj.Open();
            continue;
        }

        if (snakeObj.gameOver) {
            window.clear();
            window.draw(gameOverText);
            gameOverScoreText.setString("Score: " + std::to_string(snakeObj.score));
            window.draw(gameOverScoreText);
            window.draw(buttonShape);
            window.draw(buttonText);
            window.display();
            continue;
        }

        elapsedTime += clock.restart().asSeconds();

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && snakeObj.moveDirection != 2) {
            newMoveDirection = 0;
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && snakeObj.moveDirection != 3) {
            newMoveDirection = 1;
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && snakeObj.moveDirection != 0) {
            newMoveDirection = 2;
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && snakeObj.moveDirection != 1) {
            newMoveDirection = 3;
        }

        if (elapsedTime >= moveInterval) {
            // Update snake and reset elapsed time
            if (newMoveDirection != 4) {
                snakeObj.moveDirection = newMoveDirection;
                newMoveDirection = 4;
            }
            snakeObj.Move();
            elapsedTime = 0.f;
        }

        std::string highScoreString("HighScore: ");
        std::string scoreString("Score: ");
        scoreText.setString(highScoreString + std::to_string(snakeObj.highScore) + " " + scoreString + std::to_string(snakeObj.score));

        snakeObj.Render();
        window.draw(scoreText);
        window.display();
    }

    return 0;
}