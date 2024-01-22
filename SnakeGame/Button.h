#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
	Button();
	Button(sf::Font& font, std::string string, int characterSize, sf::Color textColor, sf::Color backGroundColor, sf::Vector2f position);

	void Draw(sf::RenderWindow& windowRef) const;
	sf::Vector2f GetPosition();
	sf::FloatRect GetGlobalBounds();

	sf::RectangleShape backGround;
	sf::Text text;
private:
	
};

Button::Button()
{

}

Button::Button(sf::Font& font, std::string string, int characterSize, sf::Color textColor, sf::Color backGroundColor, sf::Vector2f position)
{
	backGround.setSize(sf::Vector2f(200.f, 50.f));
	backGround.setFillColor(backGroundColor);
	backGround.setOutlineColor(sf::Color::White);
	backGround.setOutlineThickness(2.f);
	//backGround.setOrigin(backGround.getSize() / 2.f);
	backGround.setPosition(position);

	text.setFont(font);
	text.setString(string);
	text.setCharacterSize(characterSize);
	text.setFillColor(textColor);
	text.setStyle(sf::Text::Bold);
	text.setPosition(position);
}

void Button::Draw(sf::RenderWindow& windowRef) const
{
	windowRef.draw(backGround);
	windowRef.draw(text);
}

sf::Vector2f Button::GetPosition()
{
	return backGround.getPosition();
}

sf::FloatRect Button::GetGlobalBounds()
{
	return backGround.getGlobalBounds();
}